#include <stdlib.h> /* malloc, free */

#include "vector.h"
#include "heap.h"

struct heap
{
    is_before_t func;
    void *func_param;
    vector_t *vector;
};

/***************************** forward declarations *********************************/
void SiftUp(heap_t *heap, size_t i);
void SiftDown(heap_t *heap, size_t i);
void SwapPtr(void *a, void *b);
int IsMatch(heap_t *heap, const void *data1, const void *data2);

/******************************* API functions *************************************/

heap_t *HEAPCreate(is_before_t func, void *param)
{
    heap_t *heap = NULL;

    heap = (heap_t *)malloc(sizeof(*heap));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->func = func;
    heap->func_param = param;
    heap->vector = VectorCreate(10, sizeof(void *));

    return heap;
}

int HEAPPush(heap_t *heap, const void *data)
{
    int status = 0;

    status = VectorPushBack(heap->vector, &data);
    if (0 == status && VectorSize(heap->vector) > 1)
    {
        SiftUp(heap, HEAPSize(heap) - 1);
    }

    return status;
}

void HEAPPop(heap_t *heap)
{
    void *root = VectorGetItemAddress(heap->vector, 0);
    void *last = VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1);

    SwapPtr(root, last);
    VectorPopBack(heap->vector);
    SiftDown(heap, 0);
}

void *HEAPPeek(heap_t *heap)
{
    return *(void **)VectorGetItemAddress(heap->vector, 0);
}

size_t HEAPSize(const heap_t *heap)
{
    return VectorSize(heap->vector);
}

int HEAPIsEmpty(const heap_t *heap)
{
    return (VectorSize(heap->vector) == 0);
}

void HEAPErase(heap_t *heap, is_match_t IsMatch, void *key)
{
    size_t i = 0;
    void *saver = NULL;

    for (i = 0; i < HEAPSize(heap); i++)
    {
        saver = VectorGetItemAddress(heap->vector, i);

        if (IsMatch(*(void **)saver, key))
        {
            SwapPtr(VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1), saver);
            VectorPopBack(heap->vector);

            SiftUp(heap, i);
            SiftDown(heap, i);

            break;
        }
    }
}

void *HEAPFind(heap_t *heap, is_match_t IsMatch, void *key)
{
    size_t i = 0;
    void *saver = NULL;

    for (i = 0; i < HEAPSize(heap); i++)
    {
        saver = VectorGetItemAddress(heap->vector, i);

        if (IsMatch(*(void **)saver, key))
        {
            return *(void **)saver;
        }
    }

    return NULL;
}

void HEAPDestroy(heap_t *heap)
{
    VectorDestroy(heap->vector);

    free(heap);
    heap = NULL;
}

/*******************************************************************************/

void SiftUp(heap_t *heap, size_t i)
{
    void *parent = NULL;
    void *new = NULL;

    if (i <= 0)
    {
        return;
    }

    new = VectorGetItemAddress(heap->vector, i);
    parent = VectorGetItemAddress(heap->vector, (i - 1) / 2);

    if (heap->func(*(void **)parent, *(void **)new, heap->func_param))
    {
        SwapPtr(parent, new);

        i = (i - 1) / 2;
        SiftUp(heap, i);
    }
}

void SiftDown(heap_t *heap, size_t i)
{
    size_t child1_inx = 2 * i + 1;
    size_t child2_inx = 2 * i + 2;
    void *parent = NULL;
    void *child1 = NULL;
    void *child2 = NULL;
    void *biggest_child = NULL;

    if (child1_inx >= VectorSize(heap->vector))
    {
        return;
    }

    parent = VectorGetItemAddress(heap->vector, i);
    child1 = VectorGetItemAddress(heap->vector, child1_inx);
    child2 = VectorGetItemAddress(heap->vector, child2_inx);

    if (child2_inx >= HEAPSize(heap) || heap->func(*(void **)child2, *(void **)child1, heap->func_param))
    {
        biggest_child = child1;
        i = child1_inx;
    }
    else
    {
        biggest_child = child2;
        i = child2_inx;
    }

    if (heap->func(*(void **)biggest_child, *(void **)parent, heap->func_param))
    {
        return;
    }

    SwapPtr(parent, biggest_child);
    SiftDown(heap, i);
}

void SwapPtr(void *a, void *b)
{
    size_t temp = *(size_t *)a;
    *(size_t *)a = *(size_t *)b;
    *(size_t *)b = temp;
}

int IsMatch(heap_t *heap, const void *data1, const void *data2)
{
    return !heap->func(data1, data2, heap->func_param) &&
           !heap->func(data2, data1, heap->func_param);
}
