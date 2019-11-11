/*******************************************************************************
*	Description: circular_buffer							   		           *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: David Zarud									 	 	           *
*	Status:	Sent									 	  	         		   *
*	Last Update: 9.5.19									  	         	       *
*******************************************************************************/

#include <stdio.h>		/* puts */
#include <stdlib.h>		/*malloc*/
#include <assert.h>		/*assert*/
#include <string.h>		/*memcpy*/
#include <errno.h>      /*errno */

#include "circular_buffer.h"

#define UNUSED_VAR(x) (void)(x)
#define OVERFLOW_GUARD      (1)

struct c_buff
{
	char *read;         /*pointer to Data, first byte that hasn't been read*/
	char *write;        /*  pointer to Data, first byte you can write to   */
	size_t capacity;    /*          fixed size of size of buffer           */
	char data[1];       /*      overlapping between Meta Data and Data     */
};

/*reports errors EOVERFLOW or ENODATA*/
int g_errno = 0;

c_buff_t *CBCreate(size_t capacity)
{   
    /*allocate an extra byte*/
    c_buff_t *cb = malloc(sizeof(c_buff_t) + capacity + OVERFLOW_GUARD);

    if (NULL == cb)
    {
        puts("Malloc Failed!");
        return NULL;
    }
    
    /*increase capacity by 1 for full usage of the buffer*/
    cb->capacity = capacity + OVERFLOW_GUARD;
    cb->read = cb->data;
    cb->write = cb->data;
    
    return cb;
}

void CBDestroy(c_buff_t *cb)
{
    assert(cb);
    
    cb->write = NULL;
    cb->read = NULL;
    free(cb);
}


size_t CBGetCapacity(const c_buff_t *cb)
{
    assert(cb);
    
    return (cb->capacity - OVERFLOW_GUARD);
}


size_t CBGetFreeSpace(const c_buff_t *cb)
{
    assert(cb);
    
    if (cb->read <= cb->write)                          /*read befor write*/
    {
        return (CBGetCapacity(cb) - (cb->write - cb->read));
    }
    
    return (cb->read - cb->write - OVERFLOW_GUARD);     /*read after write*/
}

/*boolean value 1 for empty - is there new data to read or not*/
int CBIsEmpty(const c_buff_t *cb)
{ 
    assert(cb);
   
    return (cb->read == cb->write);
}

ssize_t CBWrite(c_buff_t *cb, const void *buf ,size_t count)
{
    size_t copy_part1 = 0;
    size_t copy_part2 = 0;
    
    assert(cb);
    assert(buf);
     /*when not enough bytes to write on - initialize to the max available*/
    if (count > CBGetFreeSpace(cb))
    {                                     
        count = CBGetFreeSpace(cb);
        g_errno = EOVERFLOW;            /*report attemption to overflow*/
    } 
    
    /*when writing in two parts needed*/
    if ((cb->write + count) > (cb->data + cb->capacity))
    {
        copy_part1 = cb->data + cb->capacity - cb->write;
        copy_part2 = count - copy_part1;       
             
        memcpy(cb->write, buf, copy_part1);         /* copy part 1 */
        cb->write = cb->data;                   
        
        memcpy(cb->write, (char*)buf + copy_part1, copy_part2); /*copy part 2*/
        cb->write += copy_part2;                              
        
        return (copy_part1 + copy_part2);      
    }
    
    memcpy(cb->write, buf, count);   /*regular copy */
    cb->write += count;           
        
    return count;
}

/* ENODATA buffer is empty */
ssize_t CBRead(c_buff_t *cb, void *buf ,size_t count)
{
    size_t read_part1 = 0;
    size_t read_part2 = 0;
    
    assert(cb);
    
    /*when not enough bytes to read - initialize to the max available*/
    if (count > (CBGetCapacity(cb) - CBGetFreeSpace(cb)))
    {
        count = CBGetCapacity(cb) - CBGetFreeSpace(cb);
        
        g_errno = ENODATA;                                     /*report error*/
    }
    
    /*when reading in two parts needed*/
	if ((cb->data + cb->capacity) < (cb->read + count))
    {
        read_part1 = cb->data + cb->capacity - cb->read;
        read_part2 = count - read_part1;
        
        memcpy(buf, cb->read, read_part1);                      /*read part 1*/
        cb->read = cb->data;
        
        memcpy((char*)buf + read_part1, cb->read, read_part2);
        cb->read += read_part2;
        
        return (read_part1 + read_part2);
    }
    
    memcpy(buf, cb->read, count);
	cb->read += count;
    
    return count;
}










