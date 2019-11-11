#define _POSIX_SOURCE  			/*struct sigaction */
#define _XOPEN_SOURCE			/*sys V semaphore */

#define SEM_KEY  (0x1984)
#define UNUSED(x) (void)(x)

/**************************************************************************************/

/*header fils */
#include "sched.h"
#include "uuid.h"
#include "wdAPI.h"

/**************************************************************************************/

int main()
{
	WDstart(0);

    return 0;
}
