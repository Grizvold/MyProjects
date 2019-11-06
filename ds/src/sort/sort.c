#include <stddef.h> /*    size_t    */
#include <stdlib.h> /* malloc/free  */

#include "sort.h"

/************************** Auxiliary Component *******************************/
static void MemberSwap(int *x, int *y);
/******************************************************************************/

/************************** Sorting Functions *********************************/
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
                MemberSwap(&arr[j], &arr[j+1]);
            }
        }
        
    }
}

void OptimizedBubbleSort(int *arr, size_t arr_size)
{
    size_t i = 0;
    size_t j = 0;
    size_t num_of_swaps = 1;

    for(i = 0; num_of_swaps != 0 && i < arr_size - 1; i++)
    {
        num_of_swaps = 0;
        for (j = 0; j < arr_size - i - 1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                MemberSwap(&arr[j], &arr[j+1]);
                num_of_swaps = 1;
            }
        }
    }
}

void InsertionSort(int *arr, size_t arr_size)
{
    ptrdiff_t itr = 0;
    ptrdiff_t compare_index = 0;
    int current_item = 0;

    for(itr = 1; itr < (ptrdiff_t)arr_size; ++itr)
    {
        current_item = arr[itr];

        for(compare_index = itr - 1; 
            compare_index >= 0 && arr[compare_index] > current_item;
            --compare_index)
        {
            arr[compare_index + 1] = arr[compare_index];
        }

            arr[compare_index + 1] = current_item;
    }    
}

void SelectionSort(int *arr, size_t arr_size)
{
    size_t i = 0;
    size_t j = 0;
    size_t min_index = 0;

    for(i = 0; i < arr_size - 1; i++)
    {
        min_index = i;

        for(j = i + 1; j < arr_size; j++)
        {
            if(arr[j] < arr[min_index])
            {
                min_index = j;
            }    
        }

        MemberSwap(&arr[i], &arr[min_index]);
    }
}

int CountSort(const int *original_arr, size_t arr_size, 
                int lower_limit, int upper_limit, int *sorted_arr)
{
    size_t itr = 0;
    int status = 0; /* 0 - success, 1 - failure */
    int *count_arr = NULL;
    int normalize_value = 0;
    
    normalize_value =  upper_limit - lower_limit + 1;

    count_arr = (int *)calloc(normalize_value, sizeof(int));

    for(itr = 0; itr < arr_size; itr++)
    {

    }

    return status;
}
/******************************************************************************/

/************************** Auxiliary Functions *******************************/
static void MemberSwap(int *x, int *y)
{
    int temp = 0;

    temp = *x;
    *x = *y;
    *y = temp;
}
/******************************************************************************/