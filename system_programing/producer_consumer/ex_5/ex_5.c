/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Shai Roth                                              	      */
/* Group: OL767                                                               */
/* Description: Implementation of exercises:
                                    5. M producers N comsumers 
                                        2 mutex + 2 semaphore                 */
/******************************************************************************/

#include <semaphore.h>  /* semaphore */
#include <stdio.h>      /* printf          */
#include <stdlib.h>     /* rand            */
#include <unistd.h>     /* pthread_t,pthread_mutex_t       */
#include <pthread.h>    /* pthread_create, pthread_detach, pthread_mutex_lock */

#include "cir_buffer.h" /* FSQ */

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

static pthread_mutex_t mutex_read = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_write = PTHREAD_MUTEX_INITIALIZER;
static sem_t semaphore_write;
static sem_t semaphore_read;
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
    size_t cir_buffer_capacity = 100;
    static pthread_t producer_th_arr[PRODUCER_NUM];
    static pthread_t consumer_th_arr[CONSUMER_NUM];
    static cir_buffer_t *cir_buffer = NULL;

    cir_buffer = CBCreate(cir_buffer_capacity);
    sem_init(&semaphore_write, 0, 100/8);
    sem_init(&semaphore_read, 0, 0);

    for (i = 0; i < PRODUCER_NUM; i++)
    {
        do
        {
            status = pthread_create(&producer_th_arr[i], NULL,
                                    &ProducerThread,
                                    cir_buffer);
        } while (status != 0);
    }

    for (i = 0; i < CONSUMER_NUM; i++)
    {
        do
        {
            status = pthread_create(&consumer_th_arr[i], NULL,
                                    &ConsumerThread,
                                    cir_buffer);
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

    CBDestroy(cir_buffer);
    sem_destroy(&semaphore_read);
    sem_destroy(&semaphore_write);
}

static void *ProducerThread(void *cir_buffer)
{
    size_t element = 0;
    size_t minimum_number = 1;
    size_t max_number = 100;

    while (1)
    {
        sem_wait(&semaphore_write);
        pthread_mutex_lock(&mutex_write);

        element = rand() % (max_number + 1 - minimum_number) + minimum_number;
        if(sizeof(size_t) != CBWrite(cir_buffer, &element, sizeof(size_t)))
        {
            perror("CBWrite failed \n");
            break;
        }
        printf("%sProducer CIRB Element:%s %lu thread: %lu\n", SET_BLUE_COLOR, 
                                                                RESET_COLOR, 
                                                                element,
                                                                pthread_self());
        sem_post(&semaphore_read);
        pthread_mutex_unlock(&mutex_write);
    }

    return NULL;
}

static void *ConsumerThread(void *cir_buffer)
{
    size_t element = 0;

    while (1)
    {
        sem_wait(&semaphore_read);
        pthread_mutex_lock(&mutex_read);

        if(sizeof(size_t) != CBRead(cir_buffer, &element, sizeof(size_t)))
        {
            perror("CBRead failed \n");
            break;
        }
        printf("%sConsumer CIRB element:%s %lu thread: %lu\n", SET_RED_COLOR, 
                                                                RESET_COLOR, 
                                                                element,
                                                                pthread_self());

        sem_post(&semaphore_write);
        pthread_mutex_unlock(&mutex_read);   
    }

    return NULL;
}
/******************************************************************************/
