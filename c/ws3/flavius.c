#include <stdio.h>
#include <assert.h>

int Flavius(int *soldiers, int soldiers_num);

int main()

{
    int soldiers_num = 15;
    int soldiers[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    printf("\nThe last soldier that is left : %d\n",
					Flavius(soldiers, soldiers_num));
    return 0;
}

int Flavius(int *soldiers, int soldiers_num)
{
    int i = 0;
    int dead = 0;
    int *soldier_base = soldiers;
    int kill = 0; /*don't kill*/

    assert(soldiers);

    while(dead < soldiers_num-1) /*while more then 1 soldier remain*/
    {
        while (0 == *soldiers)
        {
           if (soldiers - soldier_base == soldiers_num) /*return to base once*/
				{										/*reached array's end*/
				    soldiers = soldier_base;
				}
		  else
				{
		  		++soldiers;
				}
        }

        if (soldiers - soldier_base == soldiers_num) /*return to base once*/ 
        {											 /*reached array's end*/
            soldiers = soldier_base;				
		}
        

        if (0 != *soldiers && kill == 1)
        {
            *soldiers = 0; /*kill*/
            ++dead;

 			if (soldiers - soldier_base == soldiers_num) /*return to base once*/ 
				{										 /*reached array's end*/
				    soldiers = soldier_base;
				}
			else
            ++soldiers;

            kill = 0; /*don't kill next soldier alive*/

        }

        if (0 != *soldiers && kill == 0)
        {
			if (soldiers - soldier_base == soldiers_num) /*return to base*/ 		
					{
						soldiers = soldier_base;
					}
			else
		        ++soldiers; /*give him the sword*/
		    kill = 1; /*kill next soldier alive*/
		 
        }
    }

		

   soldiers = soldier_base;

    printf("%d dead\n", dead);
    for (i=0; i<soldiers_num; i++) /*print out the soldiers*/
    {
        printf("%i ", soldiers[i]);
    }

	while (0 == *soldiers) /*find the one that stayed alive*/
	{
		++soldiers;
	}

    return *(soldiers);
}










            

