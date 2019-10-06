#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

/* create new empty queue */
queue_t *QueueCreate();

/*  */
void QueueDestroy(queue_t *queue);

int QueueEnqueue(queue_t *element, void *data);

void *QueueDequeue(queue_t *element);

int QueueIsEmpty(const queue_t *queue);

void *QueuePeek(const queue_t *element);

size_t QueueCount(const queue_t *queue);

queue_t *QueueAppend(queue_t *dest, queue_t *src);

#endif /* queue.h */
