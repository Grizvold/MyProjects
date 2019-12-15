/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Shai Roth                                              	      */
/* Group: OL767                                                               */
/* Description: Implementation of exercises:
                                    8. Barrier (Coditional Variables)         */
/******************************************************************************/

#include <semaphore.h>  /* semaphore */
#include <stdio.h>      /* printf          */
#include <stdlib.h>     /* rand            */
#include <unistd.h>     /* pthread_t,pthread_mutex_t       */
#include <pthread.h>    /* pthread_create, pthread_detach, pthread_mutex_lock */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

#define PRODUCER_NUM 1
#define CONSUMER_NUM 10

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

static void *ProducerThread(void *data);

static void *ConsumerThread(void *data);

static size_t element = 0;

pthread_cond_t conditional_var = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
static sem_t semaphore_val;
/******************************************************************************/

int main()
{
    static pthread_t producer_th_arr[PRODUCER_NUM];
    static pthread_t consumer_th_arr[CONSUMER_NUM];
	size_t i = 0;

	sem_init (&semaphore_val, 0, 0);


	for (i = 0; i < PRODUCER_NUM; ++i)
	{
    	pthread_create(&producer_th_arr[i], NULL, ProducerThread, NULL);
	}

	for (i = 0; i < CONSUMER_NUM; ++i)
	{
    	pthread_create(&producer_th_arr[i], NULL, ConsumerThread, NULL);
	}

	for (i = 0; i < PRODUCER_NUM; i++)
    {
        pthread_join(producer_th_arr[i], NULL);
    }

    for (i = 0; i < CONSUMER_NUM; i++)
    {
        pthread_join(consumer_th_arr[i], NULL);
    }

	pthread_exit(NULL); 

    return 0;
}



/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void *ProducerThread(void *cir_buffer)
{
    size_t minimum_number = 1;
    size_t max_number = 100;
	size_t i = 0;

    while (1)
    {

		for(i = 0; i < CONSUMER_NUM; i++)
		{
        	sem_wait(&semaphore_val);
		}

        pthread_mutex_lock(&mutex_lock);

        element = rand() % (max_number + 1 - minimum_number) + minimum_number;
        printf("%sProducer Element:%s %lu thread: %lu\n", SET_BLUE_COLOR, 
                                                                RESET_COLOR, 
                                                                element,
                                                                pthread_self());
        pthread_cond_broadcast(&conditional_var);
        pthread_mutex_unlock(&mutex_lock);
    }

    return NULL;
}

static void *ConsumerThread(void *cir_buffer)
{
    while (1)
    {
        pthread_mutex_lock(&mutex_lock);
		sem_post(&semaphore_val);

		pthread_cond_wait(&conditional_var, &mutex_lock);
        printf("%sConsumer element:%s %lu thread: %lu\n", SET_RED_COLOR, 
                                                                RESET_COLOR, 
                                                                element,
                                                                pthread_self());

        pthread_mutex_unlock(&mutex_lock);   
    }

    return NULL;
}

/******************************************************************************/