#include <stddef.h> /*    size_t    */
#include <stdlib.h> /* malloc/free  */
#include <stdio.h>  /*  perror      */
#include <ulimit.h> /*  CHAR_BIT    */
#include <string.h> /*    memcpy    */

#include "sort.h"

/************************** Auxiliary Component *******************************/
static void MemberSwap(int *x, int *y);
static void ResetHistorgram(size_t *histagram_arr, size_t histagram_size);
static void CountRadix(size_t *original_arr, size_t *result_arr, 
                        size_t arr_size, size_t *histagram_arr,  
                        size_t n_bits, size_t itr);
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

/*  Unlike BubbleSort that always runs O(n^2) */
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
    ptrdiff_t itr = 0;
    int status = 0; /* 0 - success, 1 - failure */
    int range = 0;
    int *count_arr = NULL;
    int count_arr_elem = 0;

    range =  upper_limit - lower_limit + 1;

    count_arr = (int *)calloc(range, sizeof(int));

    if(NULL == count_arr)
    {
        status = 1;
        perror("Calloc failed in CountSort");

        return status;
    }

    for(itr = 0; itr < (ptrdiff_t)arr_size; itr++)
    {
        count_arr[original_arr[itr] - lower_limit]++;
    }

    for(itr = 1; itr < range; itr++)
    {
        count_arr[itr] += count_arr[itr - 1]; 
    }

    for(itr = (ptrdiff_t)arr_size - 1; itr >= 0; itr--)
    {
        count_arr[original_arr[itr] - lower_limit]--;
        count_arr_elem = count_arr[original_arr[itr] - lower_limit];
        sorted_arr[count_arr_elem] = original_arr[itr];
    }

    free(count_arr);

    return status;
}

int RadixSort(size_t *original_arr, size_t arr_size, size_t n_bits)
{
    size_t *result_arr = NULL;
    size_t *histagram_arr = NULL;
    size_t histagram_size = 0;
    size_t num_of_iteractions = 0;
    size_t itr = 0;
    int status = 0; /* 0 - success, 1 - failure */
    
    result_arr = (size_t *)malloc(sizeof(size_t) * arr_size);
    if(NULL == result_arr)
    {
        perror("Malloc in RadixSort failed");
        status = 1;

        return status;
    }

    histagram_size = 1U<<n_bits;
    histagram_arr = (size_t *)calloc(sizeof(*histagram_arr), histagram_size);
    if(NULL == histagram_arr)
    {
        perror("Calloc in RadixSort failed");
        status = 1;
        free(result_arr);

        return status;
    }

    num_of_iteractions = (sizeof(size_t) * __CHAR_BIT__) / n_bits;
    if((sizeof(size_t) * __CHAR_BIT__) % n_bits != 0)
    {
        num_of_iteractions++;
    }
    
    for(itr  = 0; itr != num_of_iteractions; itr++)
    {
        ResetHistorgram(histagram_arr, histagram_size);
        CountRadix(original_arr, result_arr, arr_size, 
                                        histagram_arr,  n_bits, itr);
        memcpy(original_arr, result_arr, arr_size * sizeof(size_t));
    }

    free(result_arr);
    free(histagram_arr);

    return status;
}
/******************************************************************************/

/************************** Auxiliary Functions *******************************/
static void ResetHistorgram(size_t *histagram_arr, size_t histagram_size)
{
    size_t itr = 0;

    for(itr = 0; itr < histagram_size; itr++)
    {
        histagram_arr[itr] = 0;
    }
}

static void CountRadix(size_t *original_arr, size_t *result_arr, 
                        size_t arr_size, size_t *histagram_arr,  
                        size_t n_bits, size_t iteration)
{
    ptrdiff_t itr = 0;
    size_t mask = 0;
    size_t orig_num_bits = 0;
    size_t histagram_size = 0;

    histagram_size = 1U<<n_bits;
    mask = (1U << n_bits) - 1;

    for(itr = 0; itr < (ptrdiff_t)arr_size; itr++)
    {
        orig_num_bits = original_arr[itr] >> (iteration * n_bits);
        orig_num_bits &= mask;   
        histagram_arr[orig_num_bits]++;
    }

    for(itr = 1; itr < (ptrdiff_t)histagram_size; itr++)
    {
        histagram_arr[itr] += histagram_arr[itr - 1];
    }

    for(itr = (ptrdiff_t)arr_size - 1; itr >= 0; itr--)
    {
        orig_num_bits = original_arr[itr] >> (iteration * n_bits);
        orig_num_bits &= mask;   
        histagram_arr[orig_num_bits]--;
        result_arr[histagram_arr[orig_num_bits]] = original_arr[itr];
    }
}


static void MemberSwap(int *x, int *y)
{
    int temp = 0;

    temp = *x;
    *x = *y;
    *y = temp;
}
/******************************************************************************/