#include <stddef.h>

#include "sort.h"

static void BubbleSortSwap(int *x, int *y);

void BubbleSort(int *arr, size_t arr_size)
{
    size_t i = 0;
    size_t j = 0;

    for(i = 0; i < arr_size - 1; i++)
    {
        for (j = 0; j < arr_size - i - 1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                BubbleSortSwap(&arr[j], &arr[j+1]);
            }
        }
        
    }
}

static void BubbleSortSwap(int *x, int *y)
{
    int temp = 0;

    temp = *x;
    *x = *y;
    *y = temp;
}