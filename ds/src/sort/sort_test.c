#include <stdio.h>  /*      printf       */
#include <stddef.h> /*      size_t       */
#include <stdlib.h> /*      srand        */
#include <time.h>   /*      time/clock   */

#include "sort.h"

#define SET_RED_COLOR "\033[0;31m"  
#define RESET_COLOR "\033[0m"

/************************** Auxiliary Component *******************************/
static void PrintIntArr(int *arr, size_t arr_size);
static void PrintArrSizeT(size_t *arr, size_t arr_size);
static void ArrValueRandomizer(int *arr, size_t arr_size);
static void PositiveArrValueRandomizer(size_t *arr, size_t arr_size);

/* Time evaluation components */
static clock_t start_time = 0;
static clock_t end_time = 0;
static double cpu_time_used = 0;
/******************************/
static int int_arr[10] = {0}; 
static size_t size_t_arr[10] = {0}; 
static const size_t arr_size = 10; /* update to size of array */
static const char print_str[] = "============================================="; 
/******************************************************************************/

/**************************** Test Functions **********************************/
void BubleSortTest();
void OptimizedBubbleSortTest();
void InsertionSortTest();
void SelectionSortTest();
void CountSortTest();
void RadixSortTest();
/******************************************************************************/

int main()
{
    /* Use current time as seed for random generator */
    srand(time(NULL));
    
    /* Buble Sort Test */
    BubleSortTest();

    /* Optimized Buble Sort Test */
    OptimizedBubbleSortTest(); 

    /* Insertion Sort Test */
    InsertionSortTest(); 

    /* Selection Sort Test */
    SelectionSortTest();

    /* Count Sort Test */
    CountSortTest(); 

    /* RadixSort Sort Test */
    RadixSortTest();

    return 0;
}

/**************************** Test Functions **********************************/
void BubleSortTest()
{
    printf("\n\t%sBuble Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(int_arr, arr_size);
    PrintIntArr(int_arr, arr_size);

    /* calculate time taken by process */
    start_time = clock();
    BubbleSort(int_arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    PrintIntArr(int_arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
}
void OptimizedBubbleSortTest()
{
    printf("\n\t%sOptimized Buble Sort ACountSortTest();lgo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(int_arr, arr_size);
    PrintIntArr(int_arr, arr_size);
    /* calculate time taken by process */
    start_time = clock();
    OptimizedBubbleSort(int_arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    PrintIntArr(int_arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
}

void InsertionSortTest()
{
    printf("\n\t%sInsertion Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(int_arr, arr_size);
    PrintIntArr(int_arr, arr_size);
    /* calculate time taken by process */
    start_time = clock();
    InsertionSort(int_arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
   
    PrintIntArr(int_arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
}

void SelectionSortTest()
{
    printf("\n\t%sSelection Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(int_arr, arr_size);
    PrintIntArr(int_arr, arr_size);
    /* calculate time taken by process */
    start_time = clock();
    SelectionSort(int_arr, arr_size);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;


    PrintIntArr(int_arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
}

void CountSortTest()
{
    int random_limit_upper = 30;
    int random_limit_lower = -20;
    static int *sorted_arr = NULL;

    sorted_arr = (int *)malloc(sizeof(int) * arr_size);

    printf("\n\t%sCount Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    ArrValueRandomizer(int_arr, arr_size);
    PrintIntArr(int_arr, arr_size);
    /* calculate time taken by process */
    start_time = clock();
    CountSort(int_arr, arr_size, random_limit_lower, random_limit_upper, sorted_arr);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    PrintIntArr(sorted_arr, arr_size);
    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);

    free(sorted_arr);
}

void RadixSortTest()
{
    size_t n_bits = 3;

    printf("\n\t%sRadix Sort Algo%s\n", SET_RED_COLOR, RESET_COLOR);
    puts(print_str);
    PositiveArrValueRandomizer(size_t_arr, arr_size);
    PrintArrSizeT(size_t_arr, arr_size);

    /* calculate time taken by process */
    start_time = clock();
    RadixSort(size_t_arr, arr_size, n_bits);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    PrintArrSizeT(size_t_arr, arr_size);

    printf("\nTime taken by process: %f\n", cpu_time_used);
    puts(print_str);
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

static void PositiveArrValueRandomizer(size_t *arr, size_t arr_size)
{
    size_t i = 0;
    size_t random_limit_upper = 500;
    
    for(i = 0; i < arr_size; i++)
    {
        arr[i] = rand() % random_limit_upper;
    }
}

static void PrintIntArr(int *arr, size_t arr_size)
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

static void PrintArrSizeT(size_t *arr, size_t arr_size)
{
    size_t itr = 0;

    printf("\n");
    for (itr = 0; itr < arr_size - 1; itr++)
    {
        printf("%ld, ", arr[itr]);
    }

    printf("%ld ", arr[itr]);
    printf("\n");
}
/******************************************************************************/
