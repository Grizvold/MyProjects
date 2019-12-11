/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Hadas Jakoubovitsh                                               */
/* Group: OL767                                                               */
/* Description: Implementation of exercises:
                                    1. 1 Producer 1 Consumer                  */
/******************************************************************************/

#include <stdio.h>   /* printf          */
#include <stdlib.h>  /* rand            */
#include <unistd.h>  /* pthread_t,pthread_mutex_t       */
#include <pthread.h> /* pthread_create, pthread_detach, pthread_mutex_lock   */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

#define SIZE 100000 /* size of arrays */
#define CONSUMER_DATA 0
#define PRODUCER_DATA 1

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";


static void ProducerConsumer(); 

static void *ProducerThread(void *data);

static void *ConsumerThread(void *data);

__sig_atomic_t flag_t = 0;
__sig_atomic_t shared_num = 0;

/******************************************************************************/

int main()
{
    ProducerConsumer();

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void ProducerConsumer()
{
    pthread_t producer_th;
    pthread_t consumer_th;
    int status = 0;

    do
    {
        status = pthread_create(&producer_th, NULL, &ProducerThread, NULL);
    }while (status != 0);

    do
    {
        status = pthread_create(&consumer_th, NULL, &ConsumerThread, NULL);
    }while (status != 0);

    pthread_join(producer_th, NULL);
    pthread_join(consumer_th, NULL);

}

static void *ProducerThread(void *data)
{

    size_t max_number = 100;
    size_t minimum_number = 1;

    (void)data;
    while (1)
    {
        while (flag_t != PRODUCER_DATA){}
        
        shared_num = rand() % (max_number + 1 - minimum_number) + minimum_number;
        printf("%sProduced number:%s %u\n", SET_BLUE_COLOR, RESET_COLOR, shared_num);
        flag_t = CONSUMER_DATA;
    }
    

    return NULL;
}

static void *ConsumerThread(void *data)
{
    (void)data;

    while (1)
    {
        while (flag_t != CONSUMER_DATA){}

        printf("%sConsumed number:%s %u\n", SET_RED_COLOR, RESET_COLOR, shared_num);
        flag_t = PRODUCER_DATA;
    }
    
    return NULL;
}
/******************************************************************************/
