/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Hadas Jakoubovitsh                                               */
/* Group: OL767                                                               */
/* Description: Implementation of exercises: 
                                        4. Sum of number divisors             */
/******************************************************************************/

#include <time.h>    /* time    */
#include <stdio.h>   /* printf  */
#include <unistd.h>  /* pthread_t,pthread_mutex_t       */
#include <pthread.h> /* pthread_create, pthread_detach, pthread_mutex_lock   */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

#define NUM_OF_THREADS 10

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

typedef struct 
{
    size_t start_of_block;
    size_t end_of_block;
    size_t requested_num;
} block_t;

static pthread_t arr_thread[NUM_OF_THREADS];

static size_t requested_num_g = 100; /* requested number to run on */

/*  -Execution function of thread. */
static void *ThreadFunc(void *var);

/*  -Return sum of divisors of requested number. */
static size_t SumOfDivisors(size_t num, size_t num_of_threads);
/******************************************************************************/

int main()
{
    clock_t start_time = 0;
    clock_t end_time = 0;
    double cpu_time_used = 0;
    size_t i = 0;

    for(i = 1; i < NUM_OF_THREADS; i++)
    {
        start_time = clock();
        printf("%sSum of all divisors:%s %lu \n", SET_BLUE_COLOR, 
                                                RESET_COLOR ,
                                                SumOfDivisors(requested_num_g,
                                                                i));    
        end_time = clock();


        cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("%sTime taken by process:%s %f, number of threads:%lu\n\n", 
                                                                SET_RED_COLOR,
                                                                RESET_COLOR,
                                                                cpu_time_used,
                                                                i);
    }

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void *ThreadFunc(void *local_block)
{

    size_t  i = 0;
    size_t start_block = 0;
    size_t end_block = 0;
    size_t num = 0;
    size_t temp_sum = 0;

    start_block = ((block_t *)local_block)->start_of_block;
    end_block = ((block_t *)local_block)->end_of_block;
    num = ((block_t *)local_block)->requested_num;

    for (i = start_block, temp_sum = 0; 
        i < end_block; 
        i++)
    {
        if(0 == num % i)
        {
            temp_sum += i;
        }
    }
    
    return (size_t *)temp_sum;
}

static size_t SumOfDivisors(size_t num, size_t num_of_threads)
{
    size_t i = 0;
    int status = 0;
    size_t sum_of_devisors = 0;
    size_t sum_of_thread = 0;
    static block_t num_block[NUM_OF_THREADS];
    size_t aligned_num = 0;

    /* aligned_num = num / 2; */
    aligned_num = num;
    aligned_num = (aligned_num + num_of_threads - 1) & ~(num_of_threads - 1);

    for (i = 0; i < num_of_threads; i++)
    {
        num_block[i].start_of_block = (aligned_num / num_of_threads) * i + 1;
        num_block[i].end_of_block = (aligned_num / num_of_threads) * (i + 1) + 1;
        num_block[i].requested_num = num;

        pthread_create(&arr_thread[i], NULL, ThreadFunc, &num_block[i]);

        /* do
        {
            status = pthread_create(&arr_thread[i], NULL, ThreadFunc, &num_block[i]);
        } while (0 != status);
         */
    }

    for (i = 0; i < num_of_threads; i++)
    {
        pthread_join(arr_thread[i], (void *)&sum_of_thread);
        sum_of_devisors += sum_of_thread;
    }

    return sum_of_devisors;
}
/******************************************************************************/