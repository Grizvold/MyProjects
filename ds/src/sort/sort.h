#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */ 

/*  Algorithm that works by repeatedly swapping adjacent 
        elements if they are in wrong order.        
    Complexity:
        Best - O(n)
        Average - O(n^2)
        Worst - O(n^2)                                      */
void BubbleSort(int *arr, size_t arr_size);

/*  */
void OptimizedBubbleSort(int *arr, size_t arr_size);
void InsertionSort(int *arr, size_t arr_size);

void SelectionSort(int *arr, size_t arr_size);


#endif /* __SORT_H__ */