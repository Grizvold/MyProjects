/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Hadas Jakoubovitsh                                               */
/* Group: OL767                                                               */
/* Description: Implementation of exercises:
                                    1. Do work using 100k threads.
                                    2. While(p_create fails)
                                    3. Detach + mutex_lock + THREAD_COUNTER   */
/******************************************************************************/

#include <stdio.h>   /* printf          */
#include <unistd.h>  /* pthread_t,pthread_mutex_t       */
#include <pthread.h> /* pthread_create, pthread_detach, pthread_mutex_lock   */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

#define SIZE 100000 /* size of arrays */

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

static pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER; /* init mutex */
static size_t arr_size_t[SIZE] = {0};
static size_t THREAD_COUNTER = 0;

/*  -Execution function of thread. */
static void *ThreadFunc(void *var);

/*  -Count 0 in arr_size_t array.
    -Count error in arr_size_t array. */
static void PrintArray();
/******************************************************************************/

int main()
{
    size_t i = 0;
    int status = 0;
    pthread_t local_thread;
    
    for (i = 0; i < SIZE; i++)
    {
        do
        {
            status = pthread_create(&local_thread, NULL, ThreadFunc, (size_t *)i);
        }while (status != 0);

        pthread_detach(local_thread);
        /* pthread_join(arr_thread[i], NULL); */
    }
    
    while (SIZE != THREAD_COUNTER);

    PrintArray();

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void PrintArray()
{
    size_t i = 0;
    size_t zero_counter = 0;
    size_t error_count = 0;

    printf("After Threads\n");
    for (i = 0; i < SIZE; i++)
    {
        /* printf("%lu ", arr_size_t[i]); */
        if(0 == arr_size_t[i])
        {
            zero_counter++;
        }

        if(i != arr_size_t[i])
        {
            error_count++;
        }
    }

    printf("%sNum of zeroes:%s %lu \n", SET_BLUE_COLOR,
                                        RESET_COLOR ,
                                        zero_counter);
    printf("%sNum of errors:%s %lu \n", SET_RED_COLOR,
                                        RESET_COLOR, 
                                        error_count);
}

static void *ThreadFunc(void *var)
{
    size_t index = 0;

    pthread_mutex_lock(&mutex_lock);
    index = (size_t )var;
    arr_size_t[index] = index;
    THREAD_COUNTER++;
    pthread_mutex_unlock(&mutex_lock);

    return NULL;
}
/******************************************************************************/
