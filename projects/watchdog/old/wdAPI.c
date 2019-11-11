#define     _POSIX_C_SOURCE          199309L

#include <pthread.h>	/* pthreads		*/
#include <unistd.h>		/*	fork		*/
#include <signal.h>		/*	signals		*/
#include <stdlib.h>		/* 	exit 		*/

#define _POSIX_C_SOURCE  	199309L
#define		INTERVAL_FOR_EXEC	  3
#define		APP_EXEC_FILE		"/home/mirit/Desktop/git/arch/linux64/bin/Debug/./app.out"
#include <stdio.h>
#include <errno.h>

#include "sched.h"		/*	schedular	*/
#include "watchdog.h"

static void *KeepMeAlive(void *sched);
static status_t SignalImAlive(void *sched);
static status_t Revive(void *data);
static void SigUsr1(int sign);
static void SigUsr2(int sign);
static void RunWD(sched_t *sched);

static pid_t pid = 0;
static int g_sign_of_life = 1;

int WDStart(char *args[])
{
	pthread_t thread = 0;
	int sign1 = 0;
	int sign2 = 0;
	struct sigaction sig_act = {NULL};
	struct sigaction sig_zero = {NULL};

	sched_t *sched = SCHCreate();
	if (NULL == sched)
	{
		return 1;
	}

	sig_act.sa_handler = SigUsr1;
	sig_act.sa_flags = 0;
	sigfillset(&sig_act.sa_mask);

	/* define  */
    sign1 = sigaction(SIGUSR1, &sig_act, NULL);

    if (-1 == sign1)
    {
        perror("failed sigaction 1");
        return 1;
    }

	sig_zero.sa_handler = SigUsr2;
	sig_zero.sa_flags = 0;
	sigfillset(&sig_zero.sa_mask);

	sign2 = sigaction(SIGUSR2, &sig_zero, NULL);

	if (-1 == sign2)
    {
        perror("failed sigaction 2");
        return 1;
    }

	pid = fork();
	/* error */
    if (pid < 0)
    {
        perror("can't fork");
        return 1;
    }
    /* app */
    else if (pid > 0)
    {
		puts("init app...");

        if (1 == pthread_create(&thread, NULL, KeepMeAlive, sched))
		{
			perror("coudn't create thread");
			return 1;
		}
    }
	/* wd */
	else if (0 == pid)
	{
		puts("init wd...");
		RunWD(sched);
	}

	return 0;
}

static void RunWD(sched_t *sched)
{
	uuid_t uid = SCHAdd(sched, INTERVAL_FOR_EXEC + 1, Revive, NULL);
	
	if (UUIDIsBadUID(uid))
	{
		puts("can't add Revive to sched");
		return;
	}

	/* sleep(1) */
	SCHRun(sched);
}

static void *KeepMeAlive(void *sched)
{
	uuid_t uid1 = SCHAdd(sched, INTERVAL_FOR_EXEC, SignalImAlive, NULL);

	if (UUIDIsBadUID(uid1))
	{
		puts("can't add SignalImAlive to sched");
		return NULL;
	}

	SCHRun(sched);

	return NULL;
}

/* Task1 - App signals wd : "I'm alive" */
static status_t SignalImAlive(void *data)
{
	if (0 != kill(pid, SIGUSR1))
	{
		puts("failed kill - sigusr1");
		return SINGLE;
	}

	puts("sign = 1");

	return CYCLE;
}

/* Task2 - Revive if needed */
static status_t Revive(void *data)
{
	char *argv_file_name[] = {APP_EXEC_FILE, NULL};
	puts("checking if Resuscitasion needed...");

	if (0 == g_sign_of_life)
	{
		puts("intubate!");
		if (-1 == execvp(argv_file_name[0], argv_file_name))
		{
			perror("Resuscitasion failed");
		}
	}
	/***** Set sign of life to zero *****/
	printf("%d\n", g_sign_of_life);
	g_sign_of_life = 0;
	printf("%d\n", g_sign_of_life);

	return CYCLE;
}

/* Signal: "I'm alive!" */
static void SigUsr1(int sign)
{
	puts("I'm alive");
	g_sign_of_life = 1;
}

/* Setting the signal back to 0 */
static void SigUsr2(int sign)
{
	puts("XXXXXXXXXXXXXXX DNR XXXXXXXXXXXXXXXXX");
}
	