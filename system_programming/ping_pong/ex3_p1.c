
#define _POSIX_C_SOURCE  199309L
#define     UNUSED(x)       (void)(x)

#include <stdio.h>                  /*  O / I   */
#include <assert.h>                 /* assert   */
#include <signal.h>                 /* signals  */
#include <unistd.h>                 /*  getpid  */
#include <sys/types.h>			    /*  pid_t   */


void PrintPing(int sig, siginfo_t *sig_info, void *args);

int main()
{
    /* initializing sigaction's structs */
    struct sigaction sig_ping = {0};

    sig_ping.sa_sigaction = PrintPing;
    sig_ping.sa_flags = SA_SIGINFO;     /* queue signals - and deliver them all */
    /* don't mask any signal */
    if (-1 == sigemptyset(&sig_ping.sa_mask))
    {
        perror("sigaction failed");
        return 1;
    }   

    /* defines SIGUSR2's functionality */
    if (sigaction(SIGUSR2, &sig_ping, NULL))
    {
        perror("failed sigaction");
    }

    printf("my pid is : %d\n", getpid());

    while(1);

    return 0;
}

void PrintPing(int sig, siginfo_t *sig_info, void *args)
{
    UNUSED(sig);
    UNUSED(args);

    write(0, "PING ", 5);
    sleep(1);
    kill(sig_info->si_pid, SIGUSR1);
}