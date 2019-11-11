
#include <stdio.h>
#include <unistd.h>     /* sleep */

#include "watchdog.h"

int main(int argc, char *argv[])
{
    WDStart(argv);

    while(1);
    /*sleep(3);
  
    WDStop();*/
    
    return 0;
}