#define     _POSIX_C_SOURCE          199309L
#define     UNUSED(x)               (void)(x)
#define     INTERVAL_SIGN_LIFE            (3)

#include <stdio.h>              /*   I / O       */
#include <assert.h>             /*   assert      */
#include <stdlib.h>             /*  malloc, free */
#include <sys/types.h>          /*  pid_t        */
#include <pthread.h>            /*  threads      */
#include <sys/types.h>          /*    fork       */
#include <signal.h>	            /*  signals      */
#include <unistd.h>             /*    exec       */
#include <semaphore.h>          /*    sem        */

#include "watchdog.h"

/* MyFuncs */
int AddTasksToSched(sched_t *sched);
void *PerformSched(void *args);

/* Tasks */
static status_t ImAlive(void *data);
static status_t BringMeBackToLife(void *args);
static status_t StopSched(void *scheduler);

/* Signals */
static void SigUsr1(int sig);
static void SigUsr2(int sig);

/* flags */
int is_process_dead = 0;
int dnr = 0;

/* global flag */
pid_t pid = 0;
int im_alive = 0;

/* args for threads */
typedef struct
{
    pid_t pid;
    char **file;
    sched_t *sched;
}thread_info_t;

/* Start */
int WDStart(char *argv[])
{
    char *wd_file[] = {"./watchdog.out", NULL};
    struct sigaction sig_app = {0};
    struct sigaction sig_wd = {0};
    pthread_t thread = 0;
    thread_info_t args_for_thread;

    /*Create sched */
    sched_t *sched = SCHCreate();

    if (NULL == sched)
    {
        puts("failed creating schedualer");
        return 1;
    }

    /* Initial sigusr1 */
    sig_app.sa_handler = SigUsr1;
    sig_app.sa_flags = 0;
    if (-1 == sigemptyset(&sig_app.sa_mask))
    {
        perror("failed initializing sigaction 1");
        return 1;
    }

    /* Initial sigusr2 */
    sig_wd.sa_handler = SigUsr2;
    sig_wd.sa_flags = 0;
    if (-1 == sigemptyset(&sig_wd.sa_mask))
    {
        perror("failed initializing sigaction 2");
        return 1;
    }

    if (0 != sigaction(SIGUSR1, &sig_app, NULL) || 0 != sigaction(SIGUSR2, &sig_wd, NULL))
    {
        perror("failed defining SIGUSR1 or SIGUSR2");
        return 1;
    }

    /* initial flags */
    dnr = 0;
	is_process_dead = 0;

    pid = fork();

    /* Error */
    if (pid < 0)
    {
        perror("failed fork");
        return 1;
    }

    /* App */
    if (pid > 0)
    {
        args_for_thread.pid = pid;
        args_for_thread.file = wd_file;
        args_for_thread.sched = sched;

        assert(args_for_thread.sched);
        if (0 != pthread_create(&thread, NULL, PerformSched, &args_for_thread))
        {
            SCHDestroy(sched);
            perror("faild creating thread App");
            return 1;
        }
    }

    /* WD */
    if (0 == pid)
    {
        args_for_thread.pid = getppid();
        args_for_thread.file = argv;
        args_for_thread.sched = sched;

        assert(args_for_thread.sched);
        if (0 != pthread_create(&thread, NULL, PerformSched, &args_for_thread))
        {
            SCHDestroy(sched);
            perror("faild creating thread App");

            return 1;
        }

        if (0 != pthread_join(thread, NULL))
        {
            perror("error in join");
        }
    }

    return 0;
}

void WDStop(void)
{
    dnr = 1;

    if (0 != kill(pid, SIGKILL))
    {
        perror("can't kill process");
    }
}

/* Add tasks to sched */
void *PerformSched(void *args)
{
    uuid_t uuid1 = {0};
    uuid_t uuid2 = {0};
    uuid_t uuid3 = {0};

    thread_info_t *thread_app = (thread_info_t*)args;
   
    uuid1 = SCHAdd(thread_app->sched, INTERVAL_SIGN_LIFE, ImAlive, args);
    
    uuid2 = SCHAdd(thread_app->sched, INTERVAL_SIGN_LIFE + 1, BringMeBackToLife, args);
    
    uuid3 = SCHAdd(thread_app->sched, INTERVAL_SIGN_LIFE, StopSched, args);
   

    if (UUIDIsBadUID(uuid1) || UUIDIsBadUID(uuid2) || UUIDIsBadUID(uuid3))
    {
        puts("can't add tasks");
    }
    puts("5");

    SCHRun(thread_app->sched);
    puts("6");

    free(thread_app);
    return NULL;
}

/* The Tasks */
static status_t ImAlive(void *data)
{
    pid = ((thread_info_t*)data)->pid;
    puts("24/7 : I'm alive!");
    im_alive = 1;
    
    if (-1 == kill(pid, SIGUSR1))
    {
        puts("restarting 24/7...........");
        BringMeBackToLife(data);
    }

    return CYCLE;
}

static status_t BringMeBackToLife(void *args)
{
    char **file = ((thread_info_t*)args)->file;

    if(1 == is_process_dead)
    {
        puts("Bring Me Back To Life");

        if (-1 == execvp(file[0], file))
        {
            perror("failed exec - can't bring ps back to life");
        }
    }

    is_process_dead = 1;

    return CYCLE;
}

static status_t StopSched(void *sched)
{
    sched_t *sched_to_stop = (sched_t*)sched;
    if (1 == dnr)
    {
        SCHStop(sched_to_stop);

        return SINGLE;  /* check */
    }

    return CYCLE;
}

/* SIGNALS */
static void SigUsr1(int sig)
{
    is_process_dead = 0;
}

static void SigUsr2(int sig)
{
    puts("Do Not ressasetate");
    dnr = 1;
}

