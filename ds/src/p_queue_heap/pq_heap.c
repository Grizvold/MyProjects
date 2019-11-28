#include <stddef.h> /* size_t       */
#include <assert.h> /* assert       */
#include <stdlib.h> /* malloc,free  */
#include <stdio.h>  /* perror       */

#include "pq_heap.h"
#include "heap.h" 

struct pq
{
    heap_t *heap;
};


pq_t *PQCreate(pq_is_before_func_t func, void *param)
{
    pq_t *pq_heap = NULL;

    while(1)
    {
        pq_heap = (pq_t *)malloc(sizeof(*pq_heap));
        if(NULL == pq_heap)
        {
            perror("Malloc in PQCreate failed");                
            break;
        }

        pq_heap->heap = HEAPCreate(func, param);
        if(NULL == pq_heap->heap)
        {
            perror("Malloc in HEAPCreate in PQCreate failed");                
            break;
        }
    
        return pq_heap;
    }

    free(pq_heap->heap);
    pq_heap->heap = NULL;
    free(pq_heap);
    pq_heap = NULL;

    return NULL;
}

void PQDestroy(pq_t *queue)
{
    HEAPDestroy(queue->heap);

    free(queue);
    queue = NULL;
}

int PQEnqueue(pq_t *queue, void *data)
{
    assert(NULL != queue);
    
    return HEAPPush(queue->heap, data);
}

void *PQDequeue(pq_t *queue)
{
    void *temp_heap = NULL;

    assert(NULL != queue);
    
    temp_heap = HEAPPeek(queue->heap);

    HEAPPop(queue->heap);

    return temp_heap;
}

void *PQPeek(pq_t *queue)
{
    assert(NULL != queue);

    return HEAPPeek(queue->heap);
}

int PQIsEmpty(pq_t *queue)
{
    assert(NULL != queue);

    return HEAPIsEmpty(queue->heap);
}

size_t PQCount(pq_t *queue)
{
    assert(NULL != queue);

    return HEAPSize(queue->heap);
}

void *PQErase(pq_t *queue, pq_is_match_t cmp_func, void *param)
{
    void *temp_node = NULL;

    assert(NULL != queue);

    temp_node = HEAPFind(queue->heap, cmp_func, param);
    HEAPRemove(queue->heap, cmp_func, param);

    return temp_node;
}
