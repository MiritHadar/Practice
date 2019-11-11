
#include <stdio.h> /*for printf*/
#define SIZE_ARR 10


typedef struct DateOfBirth
{
	size_t day;
	size_t month;
	size_t year;
}dob;

typedef struct Contact
{
	char f_name[50];
	char l_name[50];
	struct DateOfBirth dob;
	size_t id;
}person;


int main()
{
	int i = 0; /*index*/

	person arr_group[SIZE_ARR] = {
						  {"yafa", "levi", {1, 1, 2000}, 123},
						  {"hana", "cohen", {1, 1, 2001}, 234},
						  {"tova", "levi", {29, 12, 1987}, 345},
						  {"yacov", "cohen", {6, 11, 1980}, 456},
						  {"shir", "levi", {7, 5, 1998}, 567},
						  {"moshe", "cohen", {15, 1, 2011}, 678},
						  {"tom", "levi", {18, 1, 2016}, 789},
						  {"chay", "cohen", {5, 3, 2018}, 890},
						  {"gabi", "levi", {8, 8, 1999}, 987},
						  {"oren", "cohen", {9, 8, 1997}, 876}
					  	};

	person arr_group_copy[SIZE_ARR];

	FILE *fp = fopen ("my_group", "w+");

	if(fp == NULL)
	{
		puts("Failed creating a data base");
	}

	fwrite(arr_group, sizeof(person), 10, fp);

	rewind(fp); /*return to beginning of file*/

	fread(arr_group_copy, sizeof(person), 10, fp);

	remove("my_group");

	fclose(fp);

	/*test - print out copied array*/
	for(i = 0; i < SIZE_ARR; ++i)
	{
		printf("%s %s, %d/%d/%d, id %d\n", arr_group_copy[i].f_name,
									arr_group_copy[i].l_name,
									arr_group_copy[i].dob.day,
									arr_group_copy[i].dob.month,
									arr_group_copy[i].dob.year,
									arr_group_copy[i].id);
	}

	return 0;
}



