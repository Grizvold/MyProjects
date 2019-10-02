#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct dll_queue dll_queue_t;

dll_queue_t *QueueCreate();

void QueueDestroy(dll_queue_t *queue);

void QueueEnque(dll_queue_t *element, void *data);

dll_queue_t *QueueDeque(dll_queue_t *element);

int QueueIsEmpty(const dll_queue_t *queue);

void *QueuePeek(const dll_queue_t *element);

size_t QueueCount(const dll_queue_t *queue);

dll_queue_t *QueueAppend(dll_queue_t *dest, dll_queue_t *src);

#endif __QUEUE_H__ /* queue.h */
