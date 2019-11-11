
#include <stdio.h>		/*printf 	*/
#include <stdlib.h>		/*atoi, rand*/
#include <time.h>

#include "knight_tour.h"

#define UNUSED(x)		(void)(x)

int main(int argc, char *argv[])
{
	int i_start = 0;
	int j_start = 0;
	size_t counter = 1;

	size_t counter_bits = 1;
	UNUSED(argc);
	/* 
	srand(time(NULL));
	i_start = rand() % SIZE;
	j_start = rand() % SIZE;

	KTPrintBoard();
	puts("");

	puts("PlayNaive\n");
	if (KTPlayNaive(i_start, j_start, counter))
	{
		KTPrintBoard();
	}
	else
	{
		puts("Naive - No Solution found.");
	}*/

	puts("PlaySmart\n");
	if (KTPlaySmart(i_start, j_start, counter))
	{
		KTPrintBoard();
	}
	else
	{
		puts("Smart - No Solution found.");
	}

	puts("PlaySmartBits\n");
	KTPlaySmartBits(atoi(argv[1]), atoi(argv[2]), counter_bits);
	KTPrintBitBoard();
	KTPrintBitPath();

    return 0;
}

