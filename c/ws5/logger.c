/******************************************************************************/
/* author: Mirit Hadar				 							  			  */		
/* reviewer: Nir Kirshalom										  			  */
/* version: Approved                                                             */
/* Last update: 19.04.19                                                      */
/******************************************************************************/

#include <stdio.h> /*for rename, printf exetra*/
#include <stdlib.h> /*for malloc, free, size_t exetra*/
#include <string.h> /*for strcmp*/

#define UNUSED_VAR(x) (void)(x)

typedef enum {success, failure, file_doesnt_exist} status;

/*Comparison Functions*/
static void GetString(char *str2);
static int ChrCmp(const char *str, const char *str1);
static int Default(const char *str, const char *str1);

/*Operation Functions*/
static status Append(const char *file_name, const char *str2);
static status Remove(const char *file_name, const char *str2);
static status Count(const char *file_name, const char *str2);
static status Exit(const char *file_name, const char *str2);
static status Prepend(const char *file_name, const char *str2);

/*structure*/
typedef struct
{
	char *string;
	int (*Compare)(const char *str1, const char *str2);
	status (*Operation)(const char *file_name, const char *str2);
}Command;

int main(int argc, char *argv[])
{

	size_t i = 0; /*index*/
	size_t status = success;

	/*initialize struct*/
	static Command log[] = {
						{"-remove\n", strcmp, Remove},
						{"-count\n", strcmp, Count},
						{"-exit\n", strcmp, Exit},
						{"<", ChrCmp, Prepend},
						{"", Default, Append}
					  };

	/*allocate memory*/
	char *str = (char *)malloc(sizeof(str) * 50);
	if (NULL == str)
	{
		puts("Error: Not enough memory sapce allocated!");
		return failure;
	}

	/*check if file name was supllied*/
	if (2 > argc)
	{
		puts("Error: No name was given to the file");
		return failure;
	}

	/*************************Run the program********************************/
	while (failure != status)
	{
		GetString(str);
		
		for (i = 0; i < 5; ++i)
		{
			if(0 == (log[i].Compare(str,log[i].string)))
			{
				status = log[i].Operation(argv[1], str);
				break;
			}
		}
	}

	free(str); str = NULL;

	return success;
}

static int Default(const char *str, const char *str1)
{
	UNUSED_VAR(str);
	UNUSED_VAR(str1);
	return success;
}

static void GetString(char *str)
{
	puts("What do you wish to do? ");

	scanf("%c", str);
		 
	while('\n' != *str)
	{
		++str;		
		scanf("%c", str);
	}

	++str;
	*str = '\0';
}

/*for prepend*/
static int ChrCmp(const char *str, const char *str1)
{
	if (*str == *str1)
	{
		return success;
	}

	return failure;
}

static status Append(const char *file_name, const char *str)
{
	FILE *fp = fopen(file_name, "a+"); 								/*open*/
	puts("\n*******Append********\n");

	if (fp == NULL)  								/*check if file opened*/
		{
			puts("cannot open the file. run again with a different name");
			return file_doesnt_exist;
		}

   	fputs(str, fp); 						  /*append the str to the file*/
	fclose(fp);

	return success;
}

static status Remove(const char *file_name, const char *str)
{
	int status = failure;
	UNUSED_VAR(str);
	puts("\n*******Remove********\n");
  	status = remove(file_name);

	if (status == success)
	{
		printf("file deleted\n\n");
		return success;
	}

	printf("Error: Can't remove file\n");

	return failure;
}

static status Count(const char *file_name, const char *str)
{
	FILE *fp = NULL; 								   		   /*ptr to file*/
	int ch = 0;	
	int count_lines = 0;
	UNUSED_VAR(str);

	fp = fopen(file_name, "r"); 									  /*open*/
	puts("\n*******Count********\n");

	if (NULL == fp)
	{
		puts("file does not exist");
		return file_doesnt_exist;
	}

	ch = fgetc(fp);
	while(ch != EOF) 
	{
		if(ch == '\n') 				  		   /*search new lines untill EOF*/
		{
			++count_lines;
		}
		ch = fgetc(fp);
	}

	printf("Number of lines: %d\n\n", count_lines); 	/*print num of lines*/
	
	fclose(fp);

	return success;
}

static status Exit(const char *file_name, const char *str)
{
	UNUSED_VAR(str);
	UNUSED_VAR(file_name);
	puts("\n*******Exit********\n");

	return failure;
}

static status Prepend(const char *file_name, const char *str_to_prepend)
{
	FILE *fp = NULL; 											/*ptr to file*/
	FILE *fp_tmp_file = NULL; 								/*ptr to tmp file*/
	char char_to_copy = '\0';
	char *tmp_file_name = "just_making_sure_this_file_name_doesnt_exist";

	fp = fopen(file_name, "r+"); 						   /*open source file*/

	puts("\n*******PrePend********\n");
	if (NULL == fp)
	{
		puts("error: the file does not exist!");
		return failure;		   /*return error when source file does not exist*/
	}

	fp_tmp_file = fopen(tmp_file_name, "r+"); 				   /*check if tmp*/
													  /*file name is occupied*/
	if(NULL != fp_tmp_file)
	{
		puts("error: tmp file name is occupied!\n");
		return failure;
	}

	fp_tmp_file = fopen(tmp_file_name, "w+");			  /*create a tmp file*/
	
	++str_to_prepend;
	while ('\0' != *str_to_prepend)  				   /*copy str to tmp file*/
	{
		fputc(*str_to_prepend, fp_tmp_file);
		++str_to_prepend;
	}

	char_to_copy = fgetc(fp); 		   	/*copy each char from fp to tmp file*/

	while (EOF != char_to_copy)
	{
		fputc(char_to_copy, fp_tmp_file); 
		char_to_copy = fgetc(fp);		  					 /*get next char*/
	}

	if (remove(file_name) == 0 &&  rename(tmp_file_name, file_name) == 0)
	{
		fclose(fp_tmp_file);
		puts("prepending successfully completed\n");

		return success;
	}

	puts("Error: prepending failed");
	fclose(fp);

return failure;	
}














