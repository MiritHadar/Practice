/*******************************************************************************
*	Description: Dynamic vector							   		               *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Gil Kremer									 	 	           *
*	Status:	Sent									 	  	         		   *
*	Last Update: 8.5.19										  	         	   *
*******************************************************************************/

#ifndef OL67_DYNAMIC_VECTOR	
#define OL67_DYNAMIC_VECTOR	

typedef struct vector vector_t;

/*************************Dynamic vector functions*****************************/

vector_t *DVCreate(size_t element_size, size_t capacity);
void DVDestroy(vector_t *v);
int DVPushBack(vector_t *v, const void *element);
int DVPopBack(vector_t *v);
void *DVItemAddress(const vector_t *v, size_t index);
size_t DVSize(const vector_t *v);
size_t DVCapacity(const vector_t *v);
int DVReserve(vector_t *v, size_t num_to_reserve);

#endif	/*	OL67_DYNAMIC_VECTOR	*/

