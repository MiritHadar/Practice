/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <time.h>
#include "ds2.h"
#include "doubly_linked_list.h"


static int RecDivision(int num, int devide_by, const int org_devide_by);

int Division(int num, int devide_by)
{
    return RecDivision(num, devide_by, devide_by);
}


static int RecDivision(int num, int devide_by, const int org_devide_by)
{
    if (devide_by > num)
    {
        return 0;
    }

    printf("%d, %d\n", num, devide_by);
    return 1 + RecDivision(num, devide_by + org_devide_by, org_devide_by);
}


int RecMultiply(int num, int mult_By)
{
    if (mult_By == 0)
    {
        return 0;
    }

    return num + RecMultiply(num, mult_By - 1);
}

int ArrangeInList (dlist_t *org_dlist, int num)
{
    dlist_t *new_dlist = DLLCreate();
    dlist_itr_t itr = NULL;
    int num_to_add = 0;

    if (NULL == new_dlist)
    {
        return 1;
    }

    if (NULL == DLLInsert(DLLBegin(new_dlist), &num, new_dlist))
    {
        return 1;
    }

    for (itr = DLLBegin(org_dlist); !DLLIsSame(itr, DLLEnd(org_dlist)); itr = DLLNext(itr))
    {
                printf("num to add : %d\n", num_to_add);

        num_to_add = *(int*)DLLGetData(itr);
        printf("num to add : %d\n", num_to_add);
        
        if (num_to_add < num)
        {
            if (NULL == DLLPushFront(new_dlist, &num_to_add))
            {
                return 1;
            }
                PrintDList(new_dlist);

        }
        else
        {
            if (NULL == DLLPushBack(new_dlist, &num_to_add))
            {
                return 1;
            }

            PrintDList(new_dlist);
        }
    }

/*     PrintDList(org_dlist);
 */
    PrintDList(new_dlist);

    DLLDestroy(new_dlist);

    return 0;
} 






