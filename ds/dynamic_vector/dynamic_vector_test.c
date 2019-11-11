/*******************************************************************************
*	Description: Dynamic vector							   		            		   *
*	Author: Mirit Hadar									  	 	       		   *
*	Reviewer: Gil Kremer									 	 	           *
*	Status:	Sent									 	  	         		   *
*	Last Update: 8.5.19										  	         	   *
*******************************************************************************/

#include <stdio.h>		/*puts*/
#include <stdlib.h>		/*free*/
#include "dynamic_vector.h"

#define UNUSED_VAR(x) (void)(x)

void TestDVCreateDestroy();
void TestDVPushBack();
void TestDVPopBack();
void TestDVItemAddress();
void TestDVReserveSizeCapacity();



int main()
{
	TestDVCreateDestroy();
	TestDVPushBack();
	TestDVPopBack();
	TestDVItemAddress();
	TestDVReserveSizeCapacity();

	return 0;
}

void TestDVCreateDestroy()
{
	vector_t *v = DVCreate(4, 3);	/*create a vector of 3 ints*/

	if (NULL == v)
	{
		puts("Creation failed!");
	}

	DVDestroy(v);
}

void TestDVPushBack()
{
	int num = 1234;
	
	vector_t *v = DVCreate(4, 3);	/*create a vector of 3 ints*/

	if(0 != DVPushBack(v, &num))
	{
		puts("Push 1 failed");
	};
	if(0 != DVPushBack(v, &num))
	{
		puts("Push 2 failed");
	};
	if(0 != DVPushBack(v, &num))
	{
		puts("Push 3 failed");
	};
	if(0 != DVPushBack(v, &num))	/*cause overflow and hence realloc*/
	{
		puts("Push 4 failed");
	};
	

	DVDestroy(v);
	
}

void TestDVPopBack()
{
	char letter = 'a';
	vector_t *v = DVCreate(1, 5);	/*create a vector of 5 chars*/
	DVPushBack(v, &letter);			/*fill in vector*/
	DVPushBack(v, &letter);
	DVPushBack(v, &letter);
	DVPushBack(v, &letter);
	DVPushBack(v, &letter);			

	if(0 != DVPopBack(v))	
	{
		puts("Pop 1 failed");
	};
	if(0 != DVPopBack(v))
	{
		puts("Push 2 failed");
	};
	if(0 != DVPopBack(v))
	{
		puts("Push 3 failed");
	};
	if(0 != DVPopBack(v))
	{
		puts("Push 4 failed");
	};
	if(0 != DVPopBack(v))
	{
		puts("Push 5 failed");
	};
	if(1 != DVPopBack(v))		/*pop all vars out*/
	{									/*pop one too much*/
		puts("Push 6 failed");
	};
						
	DVDestroy(v);
					
}

void TestDVItemAddress()
{
	char letter = 'a';
	long num = 5678;
	size_t i = 0;
	/*char item = 0;*/

	vector_t *v = DVCreate(1, 20);	/*create a vector of 20 longs*/

	for(i = 0; i < 20; ++i)			/*push in 20 chars*/
	{
		DVPushBack(v, &letter);
	}

	for(i = 0; i < 20; ++i)
	{
		if ('a' != *(char*)DVItemAddress(v, i))
		{
			puts("Item address failed");
		}
	}	
	
	DVDestroy(v);

	v = DVCreate(8, 20);	/*create a vector of 20 longs*/

	for(i = 0; i < 20; ++i)			/*push in 20 longs*/
	{
		DVPushBack(v, &num);
	}

	for(i = 0; i < 20; ++i)
	{
		if (5678 != *(long*)DVItemAddress(v, i))
		{
			puts("Item address failed");
		}
	}	


	DVDestroy(v);
}

void TestDVReserveSizeCapacity()
{
	int num = 777;

	vector_t *v = DVCreate(4, 5);	/* create a vector of 5 nums */

	if (0 != DVSize(v))				/*check size for empty vector*/
	{
		puts("DVSize for zero failed");
	}

	DVPushBack(v, &num);				/*  push 1  */

	if (1 != DVSize(v))					/*check size*/
	{
		puts("DVSize 1 failed");
	}
	if (5 != DVCapacity(v))				/*check Capacity*/
	{
		puts("DVCapacity 1 failed");
	}
	DVPushBack(v, &num);			/*push 2*/
	DVPushBack(v, &num);			/*push 3*/
	DVPushBack(v, &num);			/*push 4*/
	DVPushBack(v, &num);			/*push 5*/

	if (5 != DVSize(v))					/*check size*/
	{
		puts("DVSize 1 failed");
	}
	if (5 != DVCapacity(v))				/*check Capacity*/
	{
		puts("DVCapacity 2 failed");
	}

	DVPushBack(v, &num);			/*"over flow"*/

	if (6 != DVSize(v))					/*check size*/
	{
		puts("DVSize 6 failed");
	}
	if (10 != DVCapacity(v))				/*check Capacity*/
	{
		puts("DVCapacity 3 failed");
	}

	DVPopBack(v);
	DVPopBack(v);
	DVPopBack(v);
	DVPopBack(v);						/*pop 4 out*/
	
	if (2 != DVSize(v))					/*check size*/
	{
		puts("DVSize after pop failed");
	}
	if (5 != DVCapacity(v))				/*check Capacity*/
	{
		puts("DVCapacity after pop failed");
	}

	DVReserve(v, 10);					/*Reverse to bigger*/
	
	DVPushBack(v, &num);			/*push 3*/
	DVPushBack(v, &num);			/*push 4*/
	DVPushBack(v, &num);			/*push 5*/
	DVPushBack(v, &num);			/*push 6*/

	
	if (10 != DVCapacity(v))
	{
	    puts("DVCapacity after pop failed");
	}
	
	if (6 != DVSize(v))
	{
	    puts("DVSize after push failed");
	}
		
	DVReserve(v, 5);					/*Reverse to smaller*/
	
	if (5 != DVCapacity(v))
	{
	    puts("DVCapacity after reserve to smaller size failed");
	}
	
	if (5 != DVSize(v))
	{
	    puts("DVSize after reserve to smaller size failed");
	}
	
	DVDestroy(v);
}









