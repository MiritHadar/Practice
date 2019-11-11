
#include <stdio.h>
#include <stdlib.h> /*for system*/

void IfElse();
void SwitchCase();
void LookUpTable();
void A();
void T();
void Esc();
void EmptyFunc();

int main()

{

	IfElse();
	/*SwitchCase();*/
	/*LookUpTable();*/
	
    return 0;
}

/*if else implemantation*/

void IfElse()
{
	char pressed = '\0'; /*initialize press var*/
	/*puts("please enter a char : ");
    scanf("%c", &pressed);*/

	system("stty -icanon -echo");

	while (27 != pressed)
	{
		puts("enter a char : ");
    	scanf("%c", &pressed);
		if (pressed == 'A')
		{
			printf ("A pressed\n");

		}
		else if (pressed == 'T')
		{
			printf ("T pressed\n");

		}
	}
	system("stty icanon echo");
}

/*switch case implemantation*/

void SwitchCase()
{
	char pressed = '\0'; /*initialize press var*/
	/*puts("enter a char : ");*/

	system("stty -icanon -echo");

	while (27 != pressed)
	{
		scanf("%c", &pressed);
		switch (pressed)
		{
			case 'A' :
				{
				puts("A pressed");
				break;
				}
			case 'T' :
				{
				puts("T pressed");
				break;
				}
			default :
				break;
		}

	}
	system("stty icanon echo");
}

/*lookup table implemantation*/

void LookUpTable()
{
	char pressed = 0;

	void (*ptr_to_funcs[256])() = {NULL}; /*array of pointers to functions*/
		
		int i = 0;
		


		system("stty -icanon -echo"); /*stop echoing!*/

		for (i = 0; i < 256; i++)
		{
			ptr_to_funcs[i] = EmptyFunc;
		}	
	
		ptr_to_funcs[27] = Esc;
		ptr_to_funcs[84] = T;
		ptr_to_funcs[65] = A;

		while (27 != pressed)
		{
			scanf("%c", &pressed);
			(*ptr_to_funcs[(int)pressed])();
		}

}

/*the funcsions called*/
void A()
{
	puts("echo A pressed");
}
void T()
{
	puts("echo T pressed");
}
void Esc()
{
	system("stty icanon echo"); /*back to default*/
}
void EmptyFunc()
{
}



	
