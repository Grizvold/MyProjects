#include <stdio.h>  /*      printf       */
#include <stddef.h> /*      size_t       */
#include <stdlib.h> /*      srand        */
#include <time.h>   /*      time/clock   */

#include "sort.h"

#define SET_RED_COLOR "\033[0;31m"  
#define RESET_COLOR "\033[0m"

static void PrintArr(int *arr, size_t arr_size);
static void ArrValueRandomizer(int *arr, size_t arr_size);

int main()
{
    /* Time evaluation components */
    static clock_t start_time = 0;
    static clock_t end_time = 0;
    static double cpu_time_used = 0;
    /******************************/
    static int arr[50000] = {0};   
    static const size_t arr_size = 50000; /* update to size of array */
    char print_string[] = "==================================================="; 


    /* Use current time as seed for random generator */
    srand(time(NULL));
    
    /* Buble Sort Test */
    printf("\n\t%sBuble Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_string);
    ArrValueRandomizer(arr, arr_size);
    /*PrintArr(arr, arr_size);*/
    /* calculate time taken by process */
    start_time = clock();
    BubbleSort(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    /*PrintArr(arr, arr_size);*/
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_string);

    /* Optimized Buble Sort Test */
    printf("\n\t%sOptimized Buble Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_string);
    ArrValueRandomizer(arr, arr_size);
    /*PrintArr(arr, arr_size);*/
    /* calculate time taken by process */
    start_time = clock();
    OptimizedBubbleSort(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    /*PrintArr(arr, arr_size);*/
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_string);

    /* Insertion Sort Test */
    printf("\n\t%sInsertion Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_string);
    ArrValueRandomizer(arr, arr_size);
    /*PrintArr(arr, arr_size);*/
    /* calculate time taken by process */
    start_time = clock();
    InsertionSort(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
   
    /*PrintArr(arr, arr_size);*/
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_string);

    /* Selection Sort Test */
    printf("\n\t%sSelection Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_string);
    ArrValueRandomizer(arr, arr_size);
    /*PrintArr(arr, arr_size);*/
    /* calculate time taken by process */
    start_time = clock();
    SelectionSort(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;


    /*PrintArr(arr, arr_size);*/
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_string);

    return 0;
}

static void ArrValueRandomizer(int *arr, size_t arr_size)
{
    size_t i = 0;
    
    for(i = 0; i < arr_size; i++)
    {
        arr[i] = rand() % 50 - 20;
    }
}

static void PrintArr(int *arr, size_t arr_size)
{
    size_t i = 0;

    printf("\n");
    for (i = 0; i < arr_size - 1; i++)
    {
        printf("%d, ", arr[i]);
    }

    printf("%d ", arr[i]);
    printf("\n");
}