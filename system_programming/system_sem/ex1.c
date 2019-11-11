
#include <stdio.h>      /* I / O */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>      /* perror */


#define KEY 0x1111 

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

int main()
{
    int semid = semget(KEY, 1, 0666 | IPC_CREAT);
    struct sembuf p = {0, -1, SEM_UNDO};
    struct sembuf v = {0, +1, SEM_UNDO};
    
    printf("semid = %d\n", semid);

    if (id < 0)
    {
        perror("failed semget");
    }

    return 0;
}