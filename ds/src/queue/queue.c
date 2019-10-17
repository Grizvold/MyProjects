#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* 	perror	 */
#include <assert.h> /* 	assert	 */

#include "queue.h"

typedef struct queue_node
{
	void *data;
	struct queue_node *next;
}sll_node_t;

struct queue
{
	sll_node_t *start;
	sll_node_t *end;
	size_t counter;
};

typedef enum
{
	SUCCESS = 0,
	FAILURE = 1
}status_t; 

queue_t *QueueCreate()
{
	queue_t *new_queue = (queue_t *)malloc(sizeof(*new_queue));
	if(NULL == new_queue)
	{
		perror("Malloc QueueCreate failed");

		return NULL;
	}
	
	new_queue->start = NULL;
	new_queue->end = NULL;
	new_queue->counter = 0;

	return new_queue;
}

void QueueDestroy(queue_t *target_queue)
{
	sll_node_t *temp_queue = NULL;
	
	assert(NULL != target_queue);
	
	for(temp_queue = target_queue->start; 
		NULL != target_queue->start && target_queue->end != target_queue->start;
		temp_queue = target_queue->start)
	{
		target_queue->start = target_queue->start->next;
		free(temp_queue);
	}
	
	free(target_queue->start);
	
	free(target_queue);
}

int QueueEnqueue(queue_t *target_queue, void *data)
{
	sll_node_t *new_node = NULL;
	
	assert(NULL != target_queue);
	
	new_node = (sll_node_t *)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{
		perror("Malloc QueueEnque failed");

		return FAILURE;
	}
	
	new_node->data = data;
	new_node->next = NULL;

	if(NULL == target_queue->start) 
	{
		target_queue->start = new_node;
	}
	
	else
	{
		target_queue->end->next = new_node;
	}
	
	target_queue->end = new_node;
	target_queue->counter++;
	
	return SUCCESS;
}

void *QueueDequeue(queue_t *target_queue)
{
	sll_node_t *temp_node = NULL;
	void *temp_data = NULL;
	
	assert(NULL != target_queue);

	temp_node = target_queue->start;
	temp_data = temp_node->data;
	target_queue->start = temp_node->next;
	
	target_queue->counter--;
	
	free(temp_node);
	
	return temp_data;	
}

int QueueIsEmpty(const queue_t *target_queue)
{
	assert(NULL != target_queue);
	
	return (0 == target_queue->counter);
}

void *QueuePeek(const queue_t *target_queue)
{
	assert(NULL != target_queue);
	
	return target_queue->start->data;
}

size_t QueueCount(const queue_t *target_queue)
{
	assert(NULL != target_queue);
	
	return target_queue->counter;
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest && NULL != src);
	
	dest->end->next = src->start;
	dest->end = src->end;
	dest->counter += src->counter;
	
	src->start = NULL;
	src->end = NULL;
	src->counter = 0;
	
	return dest;
}

