#define _POSIX_SOURCE             /* for sigaction */

#include <stdio.h>	              /*     pid_t     */
#include <sys/types.h>	          /*     pid_t     */
#include <unistd.h>               /*     fork      */
#include <signal.h>               /*    signals    */


/* ################## PING ##################* */

void Ping();

static pid_t pid = 0;

int main()
{
    char *args[] = {"./child.out", NULL};

    /* initializing sigaction's structs */
    struct sigaction ping = {0};
    ping.sa_handler = Ping;
    ping.sa_flags = 0;
    sigfillset(&ping.sa_mask);     /* Ignore interrupts */

    if (sigaction(SIGUSR1, &ping, NULL))
    {
        perror("failed sigaction");
    }
    
    puts("1");

    pid = fork();

    if (pid < 0)
    {
        perror("can't fork!");
    }
    /* child */
    else if (0 == pid)
    {
        if (execvp(*args, args))
        {
            perror("can't execute");
        }
    }
    /* parent */
    else
    {
        /* Don't close the program */
        while (1);
    }

    return 0;
}

void Ping()
{
    write(0, "PING\n", 5);
    kill(pid, SIGUSR2);
}
