#define _POSIX_SOURCE 			/*struct sigaction */

#include <sys/types.h>			/*pid_t */
#include <signal.h>				/*kill */
#include <unistd.h>             /*sleep */
#include <stdio.h>

#include "wdAPI.h"

int main()
{
    unsigned int left_time = 80;
    
    WDstart(1);

    do
    {
        left_time = sleep(left_time);
    } while (left_time > 0);
    
    WDStop();

    return 0;
}
