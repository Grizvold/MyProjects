#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

static void PrintArr(int *arr, size_t arr_size);

int main()
{
    size_t i = 0;
    static int arr[10] = {0};    
    
    srand(time(NULL));

    for(i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100;
    }

    printf("\tBuble Sort Algo\n");
    printf("================================\n");
    PrintArr(&arr[0], 10);
    BubbleSort(&arr[0], 10);
    PrintArr(&arr[0], 10);
    printf("================================\n");

    

    return 0;
}

static void PrintArr(int *arr, size_t arr_size)
{
    size_t i = 0;

    printf("\n");
    for (i = 0; i < arr_size; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}