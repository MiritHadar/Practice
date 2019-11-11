
#include <stdio.h>     /*print*/

#include "new_circular_buffer.h"

#define     SIZE    10

int main()
{
    int num = 0;
    cb_t* cb = CBCreate(SIZE);
    if (NULL == cb)
    {
        printf("Failed Create  - %d\n", __LINE__);
    }

    /*fill the buf and read all of it */
    for (num = 0; num < SIZE; ++num)
    {
        CBWrite(cb, num);
    }

    for (num = 0; num < SIZE; ++num)
    {
        printf("%d\n", CBRead(cb));
    }
    
    /*second time filling the buf*/
    for (num = 0; num < SIZE; ++num)
    {
        CBWrite(cb, num * 10);
    }

    for (num = 0; num < SIZE; ++num)
    {
        printf("%d\n", CBRead(cb));
    }

    CBDestroy(cb);

    return 0;
}