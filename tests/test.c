
#define _POSIX_C_SOURCE 200112L /* required for sigaction/env variable */
#include <stddef.h>             /* size_t   */
#include <pthread.h>            /* pthread_create */
#include <unistd.h>             /* fork     */
#include <signal.h>             /* sigaction */
#include <stdlib.h>             /* malloc, setenv   */
#include <stdio.h>              /* perror   */
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>



#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) /**/
int main(int argc, char **argv)
{
    size_t count = 0;
        sem_t *sam;
    char *str = NULL;

    setenv("TEST_VAR", "0", 1);

    if(strcmp(getenv("TEST_VAR"), "0") == 0)
    {
        printf("Success \n");
    }

        printf("%s\n", getenv("TEST_VAR"));
    str = getenv("TEST_VAR");
    count = atoi(str);

    printf("count :%ld\n", count);


    sem_unlink("sem");  /*in case previous run failed to cleanup*/
        /* wd->sem = sem_open("sem", O_CREAT, SEM_PERMS, 0);
        if(wd->sem == SEM_FAILED) 
        {
            perror("sem open failed\n");
        } */



        sam = sem_open("sem", O_RDWR);

    return 0;
}