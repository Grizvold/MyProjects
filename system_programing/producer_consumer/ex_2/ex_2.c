/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Hadas Jakoubovitsh                                               */
/* Group: OL767                                                               */
/* Description: Implementation of exercises:
                                    2. M producers N comsumers                */
/******************************************************************************/

#include <stdio.h>   /* printf          */
#include <stdlib.h>  /* rand            */
#include <unistd.h>  /* pthread_t,pthread_mutex_t       */
#include <pthread.h> /* pthread_create, pthread_detach, pthread_mutex_lock   */

#include "dll.h" /* Based on DLL ADT */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

#define CONSUMER_NUM 10
#define PRODUCER_NUM 10

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

static void ProducerConsumer();

static void *ProducerThread(void *data);

static void *ConsumerThread(void *data);

static pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
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
    size_t i = 0;
    int status = 0;
    static pthread_t producer_th_arr[PRODUCER_NUM];
    static pthread_t consumer_th_arr[CONSUMER_NUM];
    static dll_t *dll_temp = NULL;

    dll_temp = DLLCreate();

    for (i = 0; i < PRODUCER_NUM; i++)
    {
        do
        {
            status = pthread_create(&producer_th_arr[i], NULL,
                                    &ProducerThread,
                                    dll_temp);
        } while (status != 0);
    }

    for (i = 0; i < CONSUMER_NUM; i++)
    {
        do
        {
            status = pthread_create(&consumer_th_arr[i], NULL,
                                    &ConsumerThread,
                                    dll_temp);
        } while (status != 0);
    }

    for (i = 0; i < PRODUCER_NUM; i++)
    {
        pthread_join(producer_th_arr[i], NULL);
    }

    for (i = 0; i < CONSUMER_NUM; i++)
    {
        pthread_join(consumer_th_arr[i], NULL);
    }

    DLLDestroy(dll_temp);
}

static void *ProducerThread(void *dll_list)
{
    size_t element = 0;
    size_t minimum_number = 1;
    size_t max_number = 100;
    size_t dll_size = 0;

    while (1)
    {
        pthread_mutex_lock(&mutex_1);

        element = rand() % (max_number + 1 - minimum_number) + minimum_number;
        DLLPushFront(dll_list, (void *)element);
        dll_size = DLLSize(dll_list);
        printf("%sProducer DLL Element:%s %lu\n", SET_BLUE_COLOR, RESET_COLOR, element);
        printf("%sProducer DLL Size:%s %lu\n", SET_BLUE_COLOR, RESET_COLOR, dll_size);

        pthread_mutex_unlock(&mutex_1);
    }

    return NULL;
}

static void *ConsumerThread(void *dll_list)
{
    size_t element = 0;
    size_t dll_size = 0;

    while (1)
    {
        if (!DLLIsEmpty(dll_list))
        {
            pthread_mutex_lock(&mutex_1);

            element = (size_t)DLLPopBack(dll_list);
            dll_size = DLLSize(dll_list);
            printf("%sConsumer DLL element:%s %lu\n", SET_RED_COLOR, RESET_COLOR, element);
            printf("%sConsumer DLL size:%s %lu\n", SET_RED_COLOR, RESET_COLOR, dll_size);

            pthread_mutex_unlock(&mutex_1);
        }
    }

    return NULL;
}
/******************************************************************************/
