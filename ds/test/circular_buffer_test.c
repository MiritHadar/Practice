/*******************************************************************************
*	Description: circular_buffer							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: David Zarud									 	 	           *
*	Status:	Sent									 	  	         		   *
*	Last Update: 9.5.19									  	         	       *
*******************************************************************************/

#include <stdio.h>		/* putss */
#include <stdlib.h>		/*malloc*/
#include <assert.h>		/*assert*/
#include <string.h>		/*memcpy*/
#include <errno.h>      /*errno */
#include "circular_buffer.h"

#define UNUSED_VAR(x) (void)(x)
#define EOVERFLOW 75
#define ENODATA 61

void TestCBFuncs();

int main()
{
    
    
    TestCBFuncs();
    
    return 0;
}

void TestCBFuncs()
{
    /*declare errno variable*/
    extern int g_errno;
    char *buf_for_write = "this is a string for copying into the buffer and so on";
    char buf_for_read[100] = {0};
    c_buff_t *cb = CBCreate(10);                /*create a CB - size 10*/
    
    if (NULL == cb)                             
    {
        puts("Create Failed");
    }
    
    if (10 != CBGetCapacity(cb))             /*Capacity - empty buf*/
    {
        puts("Capacity - empty buf failed");
    }
    
    if (10 != CBGetFreeSpace(cb))            /*FreeSpace - empty buf*/
    {
        puts("FreeSpace - empty buf failed");
    }
    
    if (1 != CBIsEmpty(cb))                  /*Is Empty - empty buf*/
    {
        puts("Is Empty - empty buf failed");
    }
    
    if (4 != CBWrite(cb, buf_for_write, 4))   /*regular write to empty buf*/
    {
        puts("regular write to empty buf failed");
    }
	
    if (4 != CBRead(cb, buf_for_read, 5))   /*too long read, in one go*/
    {
        puts("too long read, in one go failed");
    }
    
    if (0 != strncmp(buf_for_write, buf_for_read, 4))
	{
		puts("comparing text writen and readen failed");
	}
	
    if (ENODATA != g_errno)   /*too long read, in one go - report*/
    {
        puts("too long read, in one go failed to report");
    }
    
    g_errno = 0;  /*restart errno*/
    
    
    if (10 != CBWrite(cb, buf_for_write, 14))   /*writing in length of over a whole buf*/
    {
        puts("writing in length of over a whole buf failed");
    }
    
    if (EOVERFLOW != g_errno)   /*too long read, in one go - report*/
    {
        puts("too long write failed to report");
    }
    
    g_errno = 0;  /*restart errno*/
    
    
    if (10 != CBRead(cb, buf_for_read, 15))   /*too long read, two parts*/
    {
        puts("too long read, two parts");
    }
    
    if (ENODATA != g_errno)                   
    {
        puts("too long read, in one go failed to report");
    }
    
    g_errno = 0;  /*restart errno*/
    
    if (0 != CBRead(cb, buf_for_read, 1))   /*read an empty buf*/
    {
        puts("read an empty buf failed");
    }
    
    if (ENODATA != g_errno)
    {
        puts("read an empty buf failed to report");
    }
    
    g_errno = 0;  /*restart errno*/
    
    
    if (10 != CBWrite(cb, buf_for_write, 10))
    {
        puts("whole buf writing failed");
    }

    
    if (10 != CBGetCapacity(cb))            /*capacity check after writing & reading*/
    {
        puts("capacity check after writing & reading failed");
    }
    
    if (0 != CBGetFreeSpace(cb)) /*free space of a full buf*/
    {
        puts("free space of a full buf failed");
    }
    
    if (0 != CBIsEmpty(cb))     /*Is empty test to a full buf*/
    {
        puts("Is empty test to a full buf failed");
    }
    
    if (0 != CBWrite(cb, buf_for_write, 8))     /*write to a full buf*/
    {
        puts("write to a full buf failed");
    }
    
    if (EOVERFLOW != g_errno)                   
    {
        puts("write to a full buf failed to report");
    }
    
    CBDestroy(cb);              /*destroy*/
}













