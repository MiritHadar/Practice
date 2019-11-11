

#include <stdio.h>		/*puts, printf*/
#include <unistd.h>		/* execvp     */
#include <sys/types.h>	/*  pid_t     */
#include <string.h>		/*  strtok    */
#include <wait.h>		/*  wait    */


#define		SIZE		30


void Run(void);

int main()
{
	Run();

    return 0;
}

void Run(void)
{
	int i = 0;
 	pid_t pid = 0;
	int bg = 0;

	static char command[SIZE] = {0};
	char *args[SIZE] = {0};

	puts("Insert Command:\n");

	while(1)
	{
		printf("> ");
		fgets(command, SIZE, stdin);
		args[0] = strtok(command, " \n");

		if (0 == strcmp(args[0], "exit"))
		{
			break;
		}
		/* parsing the command */
		do
		{    
			++i;
            args[i] = strtok(NULL, " \n");
        } while(0 != args[i]);

		if (0 == strcmp(args[i - 1], "&"))
		{
			bg = 1;
		}

		pid = fork();

		if (-1 == pid)
		{
			perror("fork failed");
		}

		else if (0 == pid)
		{
			if (0 == bg)
			{
				args[i - 1] = NULL;
			}
			if (0 != execvp(args[0], args))
			{
				perror("can't execute");
			}
		}

		/* when pid returned positive num it means this is the parent*/
		else if (-1 == wait(NULL))
		{
			perror("Shell failed");
		}
	}
}
