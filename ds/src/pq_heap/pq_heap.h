#ifndef __PQ_H__
#define __PQ_H__

#include <stddef.h> /* size_t */

typedef struct pq pq_t;

typedef int(*pq_is_before_func_t)(const void *data1, const void *data2, void *param);

typedef int(*pq_is_match_t)(const void *data, const void *param);

pq_t *PQCreate(pq_is_before_func_t func, void *param);

void PQDestroy(pq_t *queue);

int PQEnqueue(pq_t *queue, void *data);

void *PQDequeue(pq_t *queue);

void *PQPeek(pq_t *queue);

int PQIsEmpty(pq_t *queue);

size_t PQCount(pq_t *queue);

void *PQErase(pq_t *queue, pq_is_match_t cmp_func, void *param);
#endif /* __PQ_H__ */
