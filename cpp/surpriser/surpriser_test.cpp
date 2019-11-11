/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "surpriser.hpp"

int main(void)
{
	for (size_t i = 0; i < TIMES_OF_RUN; i++)
	{
		Surpriser *todaysSurprise = GetRandomSurprise();

		todaysSurprise->SurpriseMe();

		delete[] todaysSurprise;
	}

	return 0;
}

