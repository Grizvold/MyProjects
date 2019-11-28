#include <stdio.h>

#include "heap.h"

void PushTest(heap_t *heap);
void PopTest(heap_t *heap);
void IsEmptyTest(heap_t *heap);
void SizeTest(heap_t *heap);
void RemoveTest(heap_t *heap);

int IsBefore(const void *data1, const void *data2, void *param);
int HeapIsMatch(const void *data1, const void *data2);

static int arr[10] = {34, 6, 89, 12, 45, 66, 43, 888, 23, 13};
static int max_arr[10] = {888, 89, 66, 45, 43, 34, 23, 13, 12, 6};
static int SIZE = 10;

/*colors */
#define NRM  "\x1B[0m"
#define RED  "\x1B[1;31m"
#define GRN  "\x1B[1;32m"
#define YEL  "\x1B[1;33m"


int main()
{
    heap_t *heap = NULL;

    heap = HEAPCreate(IsBefore, NULL);

    IsEmptyTest(heap);
    PushTest(heap);
    SizeTest(heap);
    PopTest(heap);
    RemoveTest(heap);

    printf("%s", NRM);

    HEAPDestroy(heap);

    return 0;
}

void PushTest(heap_t *heap)
{
    size_t i = 0;
    int largest_for_now = 0;
    int success = 0;

    printf("%sPush and Peek Test:\n", YEL);

    for (i = 0; i < SIZE; ++i)
    {
        HEAPPush(heap, &arr[i]);

        if (*(int *)HEAPPeek(heap) < largest_for_now)
        {
            success = 1;
            break;
        }

        largest_for_now = *(int *)HEAPPeek(heap);
    }

    if (HEAPSize(heap) != SIZE)
    {
        success = 1;
    }

    success == 0 ? printf("%sSUCCESS\n", GRN) : printf("%sFAILURE\n", RED);
}

void PopTest(heap_t *heap)
{
    size_t i = 0;
    int success = 0;

    printf("%sPop Test:\n", YEL);

    for (i = 0; i < SIZE; ++i)
    {
        if (*(int *)HEAPPeek(heap) != max_arr[i])
        {
            success = 1;
            break;
        }

        HEAPPop(heap);        
    }

    if (!HEAPIsEmpty(heap))
    {
        success = 1;
    }

    success == 0 ? printf("%sSUCCESS\n", GRN) : printf("%sFAILURE\n", RED);
}

void IsEmptyTest(heap_t *heap)
{
    int success = 0;

    printf("%sIsEmpty Test:\n", YEL);

    if(!HEAPIsEmpty(heap))
    {
        success = 1;
    }

    HEAPPush(heap, &arr[0]);

    if(HEAPIsEmpty(heap))
    {
        success = 1;
    }

    HEAPPop(heap);

    success == 0 ? printf("%sSUCCESS\n", GRN) : printf("%sFAILURE\n", RED);
}


void SizeTest(heap_t *heap)
{
    int success = 0;

    printf("%sSize Test:\n", YEL);

    if (HEAPSize(heap) != SIZE)
    {
        success = 1;
    }

    success == 0 ? printf("%sSUCCESS\n", GRN) : printf("%sFAILURE\n", RED);
}

void RemoveTest(heap_t *heap)
{
    size_t i = 0;

    printf("%sRemove Test:\n", YEL);

    for (i = 0; i < SIZE; ++i)
    {
        HEAPPush(heap, &arr[i]);
    }

    HEAPRemove(heap, HeapIsMatch, &arr[8]);

    HEAPSize(heap) == (SIZE - 1) ? printf("%sSUCCESS\n", GRN) : printf("%sFAILURE\n", RED);
}

/***********************************************************/

int IsBefore(const void *data1, const void *data2, void *param)
{
    return *(int *)data1 < *(int *)data2;
}


int HeapIsMatch(const void *data1, const void *data2)
{
    return *(int *)data1 == *(int *)data2;
}