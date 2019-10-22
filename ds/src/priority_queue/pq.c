#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "pq.h"
#include "sl.h"

struct pq
{
	sl_t *s_list;	
};

pq_t *PQCreate(pq_is_before_func_t func, void *param)
{
	pq_t *p_queue = NULL;

	p_queue = (pq_t *)malloc(sizeof(*p_queue));
	if (NULL == p_queue)
	{
		perror("pqcreate malloc");
		
		return NULL;
	}

	p_queue->list = SLCreate(func, param)
	if (NULL == p_queue->list)
	{
		free(p_queue);

		return NULL;
	}

	return p_queue;
}

void PQDestroy(pq_t *queue)
{
	SLDestroy(queue->s_list);
	free(queue);
}

int PQEnqueue(pq_t *queue, void *data)
{
	SLInsert(queue->s_list, data);

	return 0;
}

void *PQDequeue(pq_t *queue)
{
	return SLPopFront(queue->s_list);
}

void *PQPeek(pq_t *queue)
{
	return SLIterGetData(SLBegin(queue->s_list));
}

int PQIsEmpty(pq_t *queue)
{
	return SLIsEmpty(queue->s_list);
}

size_t PQCount(pq_t *queue)
{
	return SLSize(queue->s_list);
}

void PQErase(pq_t *queue, pq_is_match_t cmp_func, void *param)
{
	SLRemove(SLFindIf(SLBegin(queue->s_list), SLEnd(queue->s_list), func, param));
}
