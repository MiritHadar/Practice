/*******************************************************************************
*	Description: Dynamic vector							   		            		   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Gil Kremer									 	 	           *
*	Status:	Sent									 	  	         		   *
*	Last Update: 8.5.19										  	         	   *
*******************************************************************************/

#include <stdlib.h>		/*malloc*/
#include <assert.h>		/*assert*/
#include <string.h>		/*memcpy*/
#include "dynamic_vector.h"

#define UNUSED_VAR(x) (void)(x)

struct vector
{
	void *array;			/*			poiter to head				*/
	size_t capacity;		/*num of elements that array can contain*/
	size_t num_of_elements;	/*  num of elements in array currently  */
	size_t element_size;	/*			bytes in element			*/
};

vector_t *DVCreate(size_t element_size, size_t capacity)
{
	vector_t *v = (vector_t*)malloc(sizeof(vector_t));	/*malloc for struct*/

	if (NULL == v)
	{
		return NULL;
	}

	v->array = (void*)malloc(element_size * capacity);	/*malloc for vector*/

	if (NULL == v->array)
	{
		free(v);    v = NULL;

		return NULL;
	}

	v->num_of_elements = 0;
	v->element_size = element_size;

	if (0 == capacity)		/*minimal capacity is 1*/
	{
		v->capacity = 1;
	}
	else
	{
		v->capacity = capacity;
	}

	return v;
}

void DVDestroy(vector_t *v)
{
	assert(v);

	free(v->array);		v->array = NULL;
	free(v);		v = NULL;
}

int DVPushBack(vector_t *v, const void *element)
{
	void *new_arr = NULL;
    char *end_arr = NULL;
    
	assert(v);
	assert(element);
	
	new_arr = v->array;
	end_arr = (char*)v->array + (v->element_size * v->num_of_elements);
	
	if (v->capacity == v->num_of_elements)	/*if array is full realloc*/
	{										/*a new one twice the size*/
		new_arr = realloc(v->array, (v->capacity * v->element_size * 2));

		if(NULL == new_arr)
		{
			return 1;
		}

		v->array = new_arr;				/*update array's new address*/
		end_arr = (char*)v->array + (v->element_size * v->num_of_elements);
		v->capacity = v->capacity * 2;	/*		update capacity		*/
	}
	
	memcpy(end_arr, element, v->element_size);
	++(v->num_of_elements);

	return 0;
}

int DVPopBack(vector_t *v)
{
	assert(v);
	
	if(0 == v->num_of_elements)
	{
		return 1;
	}
	
	v->num_of_elements -= 1;

	if (v->num_of_elements <= (v->capacity / 4))
	{							/*when up to 1/4 of capacity used*/
		v->capacity /= 2;		/*		srink capacity by half	 */	
	}

	return 0;
}

/*returns pointer to element */
void *DVItemAddress(const vector_t *v, size_t index)
{
	char *ptr_arr = NULL;

	assert(v);
	assert(index <= v->capacity);
	
    ptr_arr = v->array;
    
	if (v->num_of_elements < (index + 1))
	{
        return NULL;
	}

	return ptr_arr + index * v->element_size;
}

size_t DVSize(const vector_t *v)
{
	assert(v);
	
	return v->num_of_elements;
}

size_t DVCapacity(const vector_t *v)
{
	assert(v);

	return v->capacity;
}

int DVReserve(vector_t *v, size_t num_to_reserve)
{
    assert(v);
    
	if (0 == num_to_reserve)					/*minimal capacity is 1*/		
	{
		num_to_reserve = 1;
		v->num_of_elements = 0;
	}
	
	if (num_to_reserve == v->capacity)		/*when new capacity equals*/					
	{										/*		the current one	  */
		return 0;
	}
	
    if (v->num_of_elements > num_to_reserve) /*update num of elements if needed*/
	{
		v->num_of_elements = num_to_reserve;
	}
	
	/*allocate new memory for array*/
	v->array = (void*)realloc(v->array, (num_to_reserve * v->element_size));

	if(NULL == v->array)								 
	{
		return 1;
	}

	v->capacity = num_to_reserve;
	
	return 0;
}














