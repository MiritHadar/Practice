
#define _POSIX_C_SOURCE  199309L
#define     UNUSED(x)       (void)(x)

#include <stdio.h>      /* O / I  */
#include <stdlib.h>     /* atoi   */
#include <assert.h>     /* assert */
#include <signal.h>               /*    signals    */
#include <sys/types.h>      /* pid funcs */
#include <unistd.h>      /* write */


void PrintPong();

static pid_t pid = 0;

int main(int argc, char *argv[])
{
    struct sigaction sig_pong = {0};

    if(2 != argc)
    {
        puts("no file");
        return 1;
    }

    pid = atoi(argv[1]);

    sig_pong.sa_handler = PrintPong;
    sig_pong.sa_flags = SA_SIGINFO;     /* queue signals - and deliver them all */

    /* don't mask any signal */
    if (-1 == sigemptyset(&sig_pong.sa_mask))
    {
        perror("sigaction failed");
        return 1;
    }  

    /* defines SIGUSR1's functionality */
    if (sigaction(SIGUSR1, &sig_pong, NULL))
    {
        perror("failed sigaction");

        return 1;
    }
    
    kill(pid, SIGUSR2);

    while(1);

    return 0;
}

void PrintPong()
{
    write(0, "PONG ", 5);
    sleep(1);
    kill(pid, SIGUSR2);
}