
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

int main(int argc, char **argv)
{
    size_t count = 0;
    char *str = NULL;

    setenv("TEST_VAR", "1", 1);

    if(strcmp(getenv("TEST_VAR"), "BLA") == 0)
    {
        printf("Success \n");
    }

        printf("%s\n", getenv("TEST_VAR"));
    str = getenv("TEST_VAR");
    count = atoi(str);

    printf("%ld\n", count);

    return 0;
}