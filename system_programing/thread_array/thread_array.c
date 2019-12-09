#include <stdio.h>   /* printf          */
#include <unistd.h>  /* pthread_t       */
#include <pthread.h> /* pthread_create  */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/
size_t arr_size_t[30000] = {0};

pthread_t arr_thread[30000];

static size_t SIZE = 30000;


void *ThreadFunc(void *var);
/******************************************************************************/

int main()
{
    size_t i = 0;
    int err = 0;
    for (i = 0; i < SIZE; i++)
    {
        err = pthread_create(&arr_thread[i], NULL, ThreadFunc, &i);
        if (err != 0)
        {
            puts("ssss");
        }
    }

    sleep(3);
    printf("After Thread\n");
    for (i = 0; i < SIZE; i++)
    {
        printf("%lu \n", arr_size_t[i]);
    }

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

void *ThreadFunc(void *var)
{
    arr_size_t[*((size_t *)var)] = *((size_t *)var);

    return NULL;
}
/******************************************************************************/
