/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 29-09-2019					                                  */
/******************************************************************************/

#include <iostream>			//	cout 	
#include <cstring>			//	memset
#include <cstdio>			//	sprintf

#include "storage.hpp"		//	Header file		

using namespace ilrd;
using namespace std;

/*************************Helper functions*************************************/
static void FirstTest();
static void SecondTest();
/******************************************************************************/

int main()
{
	FirstTest();
	SecondTest();
	
	return 0;
}

static void FirstTest()
{
	Storage s;
	char array1[DATA_BLOCK_SIZE] = {0};
	char array2[DATA_BLOCK_SIZE] = {0};

	memset(array1, 'a', DATA_BLOCK_SIZE);
	s.Write(array1, 10);
	s.Read(array2, 10);

	for(size_t i = 0; i < 10; ++i)
	{
		if (array1[i] != array2[i] || 'a' != array2[i])
		{
			cout << "Error in line " << __LINE__ << endl;
		}
	}
}

static void SecondTest()
{
    Storage storage;

    for (size_t i = 0; i < 10; i++)
    {
        char data[DATA_BLOCK_SIZE] = {0};
        sprintf(data, "%lu", i);
        storage.Write(data, i);
    }
    
    for (size_t i = 5; i < 10; i++)
    {
        char data[DATA_BLOCK_SIZE] = {0};
        sprintf(data, "%lu", i + 10);
        storage.Write(data, i);
    }

    for (size_t i = 0; i < 10; i++)
    {
        char data[DATA_BLOCK_SIZE] = {0};
        storage.Read(data, i);
        printf("%s\n", data);
    }  
}

