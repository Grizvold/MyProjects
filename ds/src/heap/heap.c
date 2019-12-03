#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* perror       */
#include <assert.h> /* assert       */

#include "heap.h"
#include "vector.h"


/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/
struct heap
{
    vector_t *vector;
    is_before_t func;
    void *func_param;
};

typedef enum{SUCCESS = 0, FAILURE} is_success_t;

void HeapHelperSiftUp(heap_t *heap, size_t index);
void HeapHelperSiftDown(heap_t *heap, size_t index);

/*  -Swaps between 2 vector cells.  */
void HeapHelperSwap(void *ptr_1, void *ptr_2);

/*  -User is_before function. Since Vector holds pointers need to do:
        casting and dereference -> *(void **).
    -Returns:
        1 if true.
        0 if false.   */
int HeapHelperIsBefore(heap_t *heap, const void *data_1, const void *data_2);
/******************************************************************************/


/******************************************************************************/
/*                          Heap Functions Definition                         */
/******************************************************************************/
heap_t *HEAPCreate(is_before_t func, void *param)
{
    heap_t *heap = NULL;

    while(1)
    {
        heap = (heap_t *)malloc(sizeof(*heap));
        if(NULL == heap)
        {
            perror("Malloc in HEAPCreate failed");

            break;
        }

        heap->func = func;
        heap->func_param = param;
        heap->vector = VectorCreate(sizeof(void *), 10);
        if(NULL == heap->vector)
        {
            perror("Memory allocation vector creation failed in HEAPCreate");

            break;
        }

        return heap;
    }

    free(heap);
    heap = NULL;

    return NULL;
}

void HEAPDestroy(heap_t *heap)
{
    VectorDestroy(heap->vector);
    
    free(heap);
    heap= NULL;
}

int HEAPPush(heap_t *heap, const void *data)
{
    is_success_t status = SUCCESS;

    status = VectorPushBack(heap->vector, &data);

    if(SUCCESS == status)
    {
        /* since index starts from 0 -> need "-1" */
        HeapHelperSiftUp(heap, HEAPSize(heap) - 1);
    }

    return status;
}

void HEAPPop(heap_t *heap)
{
    void *root = NULL;
    void *curr_node = NULL;

    root = VectorGetItemAddress(heap->vector, 0);
    curr_node = VectorGetItemAddress(heap->vector, HEAPSize(heap) - 1); 

    HeapHelperSwap(root, curr_node);

    VectorPopBack(heap->vector);

    HeapHelperSiftDown(heap, 0);
}

void *HEAPPeek(heap_t *heap)
{
    assert(NULL != heap);

    return *(void **)VectorGetItemAddress(heap->vector, 0);
}

int HEAPIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return (SUCCESS == VectorSize(heap->vector));
}

size_t HEAPSize(const heap_t *heap)
{
    assert(NULL != heap);

    return VectorSize(heap->vector);
}

void *HEAPFind(heap_t *heap, is_match_t match_func, void *data)
{
    size_t index = 0;
    void *temp_node = NULL;

    assert(NULL != heap);

    for(index = 0; HEAPSize(heap) > index; index++)
    {
        temp_node = VectorGetItemAddress(heap->vector, index);

        if(match_func(*(void **)temp_node, data))
        {

            return *(void **)temp_node;
        }
    }

    return NULL;
}

void HEAPRemove(heap_t *heap, is_match_t match_func, void *data)
{
    size_t index = 0;
    void *temp_node = NULL;

    assert(NULL != heap);

    for(index = 0; HEAPSize(heap) > index; index++)
    {
        temp_node = VectorGetItemAddress(heap->vector, index);

        /*  if we found requested element: 
                    swap -> pop from back -> perform sifting */
        if(match_func(*(void **)temp_node, data))
        {
            HeapHelperSwap(temp_node, 
                        VectorGetItemAddress(heap->vector, HEAPSize(heap) - 1));
            VectorPopBack(heap->vector);
            HeapHelperSiftUp(heap, index);
            HeapHelperSiftDown(heap, index);

            break;
        }
    }
}
/******************************************************************************/


/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/
void HeapHelperSiftUp(heap_t *heap, size_t index)
{
    void *parent = NULL;
    void *child = NULL;

    /* stop condition 1: if current index is <root> */
    if(0 == index)
    {

        return;
    }

    parent = VectorGetItemAddress(heap->vector, (index - 1) / 2);
    child = VectorGetItemAddress(heap->vector, index);

    /* stop condition 2: if parent is bigger then child */
    if(HeapHelperIsBefore(heap, child, parent))
    {
        return;
    }

    /* else swap 2 nodes and go up recursively */
    HeapHelperSwap(child, parent);
    HeapHelperSiftUp(heap, (index - 1) / 2);
}

void HeapHelperSiftDown(heap_t *heap, size_t index)
{
    void *big_child = NULL;
    void *parent = NULL;
    void *child_1 = NULL;
    void *child_2 = NULL;
    size_t index_1 = 2 * index + 1; /* 1st child */
    size_t index_2 = 2 * index + 2; /* 2nd child */

    /* stop condition 1: if 1st child doesn't exists(end of vector) */
    if(index_1 >= VectorSize(heap->vector))
    {
        return;
    }
    
    parent = VectorGetItemAddress(heap->vector, index);
    child_1 = VectorGetItemAddress(heap->vector, index_1);
    child_2 = VectorGetItemAddress(heap->vector, index_2);

    /* if 2nd child doesn't exists OR child_2 < child_1 -> go to child_1 */
    if(VectorSize(heap->vector) <= index_2 || 
        HeapHelperIsBefore(heap, child_2, child_1))
    {
        big_child = child_1;
        index = index_1;
    }
    /* if child_1 < child_2 */
    else
    {
        big_child = child_2;
        index = index_2;
    }

    /* if children are bigger than parent */
    if(HeapHelperIsBefore(heap, parent, big_child))
    {
        HeapHelperSwap(parent, big_child);
        HeapHelperSiftDown(heap, index);
    }
}

void HeapHelperSwap(void *ptr_1, void *ptr_2)
{
    size_t temp_ptr = *((size_t *)ptr_1);
    *((size_t *)ptr_1) = *((size_t *)ptr_2);
    *((size_t *)ptr_2) = temp_ptr; 
}

int HeapHelperIsBefore(heap_t *heap, const void *data_1, const void *data_2)
{
    return heap->func(*(void **)data_1, *(void **)data_2, heap->func_param);
}
/******************************************************************************/
