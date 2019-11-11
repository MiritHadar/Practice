#define _POSIX_SOURCE             /* for sigaction */

#include <stdio.h>                /*     I / O     */
#include <signal.h>               /*    signals    */
#include <sys/types.h>	          /*     pid_t     */
#include <unistd.h>               /*     fork      */

static pid_t pid = 0;

void Ping();
void Pong();

int main()
{
    int sig1 = 0;
    int sig2 = 0;
    
    /* initializing sigaction's structs */
    struct sigaction ping = {0};
    struct sigaction pong = {0};

    ping.sa_handler = Ping;
    ping.sa_flags = 0;
    sigfillset(&ping.sa_mask);     /* Ignore interrupts */

    pong.sa_handler = Pong;
    pong.sa_flags = 0;
    sigfillset(&pong.sa_mask);     /* Ignore interrupts */

    /* define  */
    sig1 = sigaction(SIGUSR1, &ping, NULL);
    sig2 = sigaction(SIGUSR2, &pong, NULL);

    if (-1 == sig1 || -1 == sig2)
    {
        puts("failed sigaction");
        return 1;
    }
    
    pid = fork();

    /* error */
    if (pid == -1)
    {
        perror("can't fork proparly");

        return 1;
    }
    /* parent */
    if (pid > 0)
    {
        kill(pid, SIGUSR2);
    }
    while (1);

    return 0;
}

void Ping()
{
    write(0, "PING\n", 5);
    kill(pid, SIGUSR2);
}

void Pong()
{
    write(0, "PONG\n", 5);
    kill(getppid(), SIGUSR1);
}