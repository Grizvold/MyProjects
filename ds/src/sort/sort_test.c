#include <stdio.h>  /*      printf       */
#include <stddef.h> /*      size_t       */
#include <stdlib.h> /*      srand        */
#include <time.h>   /*      time/clock   */

#include "sort.h"

#define SET_RED_COLOR "\033[0;31m"  
#define RESET_COLOR "\033[0m"

/************************** Auxiliary Component *******************************/
static void PrintArr(int *arr, size_t arr_size);
static void ArrValueRandomizer(int *arr, size_t arr_size);

/* Time evaluation components */
static clock_t start_time = 0;
static clock_t end_time = 0;
static double cpu_time_used = 0;
/******************************/
static int arr[10] = {0};   
static const size_t arr_size = 10; /* update to size of array */
static const char print_str[] = "============================================="; 
/******************************************************************************/

/**************************** Test Functions **********************************/
void BubleSortTest();
void OptimizedBubbleSortTest();
void InsertionSortTest();
void SelectionSortTest();
void CountSortTest();
/******************************************************************************/

int main()
{
    /* Use current time as seed for random generator */
    srand(time(NULL));
    
    /* Buble Sort Test */
    /* BubleSortTest(); */

    /* Optimized Buble Sort Test */
    /* OptimizedBubbleSortTest(); */

    /* Insertion Sort Test */
    /* InsertionSortTest(); */

    /* Selection Sort Test */
    /* SelectionSortTest(); */

    /* Count Sort Test */
    CountSortTest();

    return 0;
}

/**************************** Test Functions **********************************/
void BubleSortTest()
{
    printf("\n\t%sBuble Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(arr, arr_size);
    PrintArr(arr, arr_size);

    /* calculate time taken by process */
    start_time = clock();
    BubbleSort(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    PrintArr(arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
}

void OptimizedBubbleSortTest()
{
    printf("\n\t%sOptimized Buble Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(arr, arr_size);
    PrintArr(arr, arr_size);
    /* calculate time taken by process */
    start_time = clock();
    OptimizedBubbleSort(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    PrintArr(arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
}

void InsertionSortTest()
{
    printf("\n\t%sInsertion Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(arr, arr_size);
    PrintArr(arr, arr_size);
    /* calculate time taken by process */
    start_time = clock();
    InsertionSort(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
   
    PrintArr(arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
}

void SelectionSortTest()
{
    printf("\n\t%sSelection Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(arr, arr_size);
    PrintArr(arr, arr_size);
    /* calculate time taken by process */
    start_time = clock();
    SelectionSort(arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;


    PrintArr(arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
}

void CountSortTest()
{
    int random_limit_upper = 50;
    int random_limit_lower = 20;
    static int *sorted_arr = NULL;

    sorted_arr = (int *)malloc(sizeof(int) * arr_size);

    printf("\n\t%sSelection Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(arr, arr_size);
    PrintArr(arr, arr_size);

    CountSort(arr, arr_size, random_limit_lower, random_limit_upper, sorted_arr);
    PrintArr(sorted_arr, arr_size);

    free(sorted_arr);
}
/******************************************************************************/

/************************** Auxiliary Functions *******************************/
static void ArrValueRandomizer(int *arr, size_t arr_size)
{
    size_t i = 0;
    int random_limit_upper = 50;
    int random_limit_lower = 20;
    
    for(i = 0; i < arr_size; i++)
    {
        arr[i] = rand() % random_limit_upper - random_limit_lower;
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
/******************************************************************************/
