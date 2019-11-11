#include <stdio.h>         /*  I / O   */
#include <stdlib.h>         /*  qsort   */

#include "sort.h"           /*merge sort*/
#include "sort_shuf.h"      /* h file   */
 
static void GetInputFromUser(FILE *fp);

int Shuf(int argc, char **argv)
{
    FILE *file_name = NULL;

    if (argc < 2)
    {
        puts("error - no file supplied");

        return 1;
    }
    else
    {
        file_name = fopen(argv[1], "+w");
    }
    if (NULL == file_name)
    {
        puts("error - can't open file");

        return 1;
    }
     
    fseek(file_name, 0, SEEK_END);

    return ftell(file_name);
}
