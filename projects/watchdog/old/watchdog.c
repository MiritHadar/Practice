#define _POSIX_C_SOURCE       199309L
#define     UNUSED(x)       (void)(x)

#include <stdio.h>              /*   I / O    */
#include <unistd.h>		        /*   execvp   */
#include <sys/types.h>	        /*   pid_t    */
#include <signal.h>	            /*   signals  */

#include "watchdog.h"

int main(int argc, char *argv[])
{
    if (0 != WDStart(argv))
    {
        return 1;
    }

    return 0;
}