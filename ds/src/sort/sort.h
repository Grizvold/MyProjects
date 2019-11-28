#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */ 

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
typedef int (*is_before_t)(const void *data1, const void *data2, void *param);
/******************************************************************************/


/******************************************************************************/
/*                          Sort Functions Declaration                        */
/******************************************************************************/
/*  Algorithm that works by repeatedly swapping adjacent 
        elements if they are in wrong order.        
    Complexity:
        Best - O(n^2)
        Average - O(n^2)
        Worst - O(n^2)   
    Sorting In Place: Yes
    Stable: Yes                                   */
void BubbleSort(int *arr, size_t arr_size);

/*  Unlike BubbleSort that always runs O(n^2) even if
        the array is sorted. OptimizedBuubleSort
        stops the algorithm if the inner loop didn't do
        any swap.
    Complexity:
        Best - O(n)
        Average - O(n^2)
        Worst - O(n^2)
    Sorting In Place: Yes
    Stable: Yes                                   */
void OptimizedBubbleSort(int *arr, size_t arr_size);

/*  Algorithm that builds the final sorted array 
        (or list) one item at a time. Similar to 
        how you sort cards.
    Complexity:
        Best - O(n)
        Average - O(n^2)
        Worst - O(n^2)
    Sorting In Place: Yes
    Stable: Yes                                   */
void InsertionSort(int *arr, size_t arr_size);

/*  Algorithm that devides the input into two parts:
        the sublist of items already sorted, which 
        is build up from left to right, and the
        sublist of items remaining to be sorted.
        Algorithm finds the smallest element and
        swaps it with the leftmost unsorted element,
        and moving the sublist boundaries one element
        to the right.
    Complexity:
        Best - O(n^2)
        Average - O(n^2)
        Worst - O(n^2)
    Sorting In Place: Yes
    Stable: No                                    */
void SelectionSort(int *arr, size_t arr_size);

/* */
int CountSort(const int *original_arr, size_t arr_size, 
                int lower_limit, int upper_limit, int *sorted_arr);

/* */
int RadixSort(size_t *original_arr, size_t arr_size, size_t n_bits);

/* */
void HeapSort(void *base, size_t n_memb, size_t ele_size, is_before_t func);
/******************************************************************************/
#endif /* __SORT_H__ */