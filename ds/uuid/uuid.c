/*******************************************************************************
*	Description: sorted_linked_list							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ori Michaeli									 	 	           *
*******************************************************************************/

#include <time.h>   /* time */
#include <unistd.h> /*getpid*/

#include "uuid.h"

uuid_t bad_uid = {0, -1, 0};

uuid_t UUIDCreate(void)
{
    static size_t ctr = 0;
    
    uuid_t uuid = {0};
    uuid.pid = getpid();
	uuid.time = time(NULL);
	uuid.counter = ++ctr;
	
	if (-1 == uuid.time)
	{
	    return bad_uid;
	}
	
	return uuid;
}

int UUIDIsSame(uuid_t uid1, uuid_t uid2)
{
    return ((uid1.pid == uid2.pid) && (uid1.time == uid2.time) &&
                                               (uid1.counter == uid2.counter)); 
}

int UUIDIsBadUID(uuid_t uid)
{
    return UUIDIsSame(bad_uid, uid);
} 







