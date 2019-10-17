#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

/* *Creates empty queue that works in FIFO,
	stores addresses of elements.
   *Queue's size is not fixed.
   *Returns pointer to the created queue.			 */
queue_t *QueueCreate();

/* *Free alocated memory of targeted queue.
   *All the elements in queue will be erased.		 */
void QueueDestroy(queue_t *queue);

/* *Add new element to the tail of the queue.
   *Complexity O(1).
   *Returns status 0 - success
   			    1 - failure					 */
int QueueEnqueue(queue_t *element, void *data);

/* *Removes head (first) element of the queue.
   *Dequeueing when list is empty is undefined.		 
   *Returns data of the head (first) element.		 */
void *QueueDequeue(queue_t *element);

/* *Boolean function that checks if queue if empty.
   *Returns 1 if empty 
   		  0 if not empty.						 */
int QueueIsEmpty(const queue_t *queue);

/* *Peeks on the head (first) element of the queue.
   *Only peeks on the element and not removing it,
   		but gives option to make changes 
   		to the element.
   *Returns address of the first element of the queue.	 */
void *QueuePeek(const queue_t *element);

/* *Returns number of elements in targeted queue.
   *Complexity O(1).							 */
size_t QueueCount(const queue_t *queue);

/* *Chaining src queue items to the tail of dest 
		queue, and removing chained items from src
		queue.
   *Complexity O(1).
   *Returns chained dest queue.					 */
queue_t *QueueAppend(queue_t *dest, queue_t *src);

#endif /* __QUEUE_H__ */
