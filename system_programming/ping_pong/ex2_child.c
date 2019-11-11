#define _POSIX_SOURCE             /* for sigaction */

#include <stdio.h>	              /*     pid_t     */
#include <sys/types.h>	          /*     pid_t     */
#include <unistd.h>               /*     fork      */
#include <signal.h>               /*    signals    */

/*################## PONG ##################*/

void Pong();

int main()
{
    /* initializing sigaction's structs */
    struct sigaction pong = {0};

    pong.sa_handler = Pong;
    pong.sa_flags = 0;
    sigfillset(&pong.sa_mask);     /* Ignore interrupts */

    if (sigaction(SIGUSR2, &pong, NULL))
    {
        perror("failed sigaction");
    }

    kill(getppid(), SIGUSR1);

    while(1);

    return 0;
}

void Pong()
{
    write(0, "PONG\n", 5);
    kill(getppid(), SIGUSR1);
}
