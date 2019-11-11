#include <ctype.h> /*for tolower*/
#include <stdio.h>
#include <string.h> /*strlen*/
#include <assert.h>
#include <stdlib.h>  /*for malloc*/
#define UNUSED_VAR(x) (void)(x) /*macro for argc and argv*/


void Print_env_variables(char **buffer);

/*
The main function receives argc, argv and envp,
and copies all env variables in lowercase to a new char** */

int main (int argc, char *argv[], char *envp[])
{

	size_t len_envp = 0;                      /*initialize counter*/
    char **buffer = NULL;           /*initialize string for answer*/
	char **base_buffer = NULL;		  /*save start point of buffer*/
	char **base_envp = envp;		  /*save start point of buffer*/
	char *current_read_char = NULL;             /*char readen from*/
	char *current_write_char = NULL;              /*char writen to*/

	/*calling vars for avioding warning*/
	UNUSED_VAR(argc);
	UNUSED_VAR(argv);

	assert(envp);

	/*find length of **envp */
	while (NULL != *envp)
	{
		++len_envp;
		++envp;
	}

	/*allocate space for the buffer*/
	buffer = (char**)malloc((len_envp + 1) * sizeof(char *));


	/*check there is enough space allocated*/
    if (NULL == buffer)
        {
			puts("not enough room allocated");
            return 1;
        }

	/*restart buffer*/
	envp = base_envp;
	base_buffer = buffer;

	/*loop of mallocs for all strings*/
	while (NULL != *envp)
	{
		*buffer = (char*)malloc(strlen(*envp) * sizeof(char)+1);
		++buffer;
		++envp;
	/*free all mallocs if not enough room was allocated*/
		if (NULL != *buffer)
		{
			buffer = base_buffer;
			puts("not enough room allocated");
			while (NULL != buffer)
			{
				free(*buffer);
				++buffer;
			}
			buffer = base_buffer;
			free(buffer);
			return 1;
		}
	}
	

	/*restart buffer & envp*/
	envp = base_envp;
	buffer = base_buffer;

	/*copy env variables in to buffer*/
	/*convert variables in to lowercase*/
	
    while(NULL != *envp)
    {
		current_read_char = *envp;
		current_write_char = *buffer;
 		while('\0' != *current_read_char)
		{
			*current_write_char = tolower(*current_read_char);
			++current_write_char;
			++current_read_char;
		}
		*current_write_char = '\0';
		++envp;
		++buffer;
		
	}

	buffer = base_buffer;

	/*print out all variables in the lower case*/
	Print_env_variables(buffer);


	/*free all the buffer in the end*/

	while(NULL != *buffer)
	{
		free(*buffer);
		++buffer;
	}

	buffer = base_buffer;
	free(buffer);

	return 0;

}


/*
This function receives an array of pointers to env variables and prints it out
*/
void Print_env_variables(char **buffer)
{
    while (NULL != *buffer)
    {

        printf("%s\n", *buffer);
        ++buffer;
    }
}

