/*******************************************************************************
*	Description: uuid							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ori Michaeli									 	 	           *
*******************************************************************************/

#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include "uuid.h"

int main()
{
    uuid_t uid1 = {0};
    uuid_t uid2 = {0};
    uuid_t uid3 = {0};
    
    uid1 = UUIDCreate();
    system("sleep 1");
    
    uid2 = UUIDCreate();
    system("sleep 1");
    
    uid3 = UUIDCreate();
    system("sleep 1");
    
    printf("PID : %d\tTIME : %lu\tCOUNTER : %lu\n", uid1.pid, uid1.time,
                                                                uid1.counter);
    printf("PID : %d\tTIME : %lu\tCOUNTER : %lu\n", uid2.pid, uid2.time,
                                                                uid2.counter);
    printf("PID : %d\tTIME : %lu\tCOUNTER : %lu\n", uid3.pid, uid3.time,
                                                                uid3.counter);
    
    if (1 == UUIDIsSame(uid1, uid2))
    {
        printf("%d failure in is same\n", __LINE__);
    }
    
    if (1 != UUIDIsSame(uid3, uid3))
    {
        printf("%d failure in is same\n", __LINE__);
    }
    
    if (1 == UUIDIsBadUID(uid1))
    {
        printf("%d bad uid1\n", __LINE__);    
    }
    
    if (1 == UUIDIsBadUID(uid2))
    {
        printf("%d bad uid1\n", __LINE__);    
    }
    
    if (1 == UUIDIsBadUID(uid3))
    {
        printf("%d bad uid1\n", __LINE__);    
    }
    
    return 0;
}











