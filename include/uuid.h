/*******************************************************************************
*	Description: sorted_linked_list							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Ori Michaeli									 	 	           *
*******************************************************************************/

#ifndef OL67_UUID
#define OL67_UUID

#include <sys/types.h>	/* time_t, size_t, pid_t  */


/*==============================================================================
	
		 ____   ___  _   _ _____   _____ ___  _   _  ____ _   _ 
		|  _ \ / _ \| \ | |_   _| |_   _/ _ \| | | |/ ___| | | |
		| | | | | | |  \| | | |     | || | | | | | | |   | |_| |
		| |_| | |_| | |\  | | |     | || |_| | |_| | |___|  _  |
		|____/ \___/|_| \_| |_|     |_| \___/ \___/ \____|_| |_|
*/	

			                                            
typedef struct uuid
{
	pid_t pid;
	time_t time;
	size_t counter;
	
} uuid_t;

extern uuid_t bad_uid;
			                                             
/*============================================================================*/


/* Generates a unique id */
uuid_t UUIDCreate(void);

/* Checks if 2 uids are the same  */
int UUIDIsSame(uuid_t uid1, uuid_t uid2);

/* Check if uid is valid */
int UUIDIsBadUID(uuid_t uid);

#endif /* OL67_UUID */
