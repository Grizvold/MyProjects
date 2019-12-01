#include <stddef.h> /*      size_t       */
#include <stdio.h>  /*      printf       */
#include <time.h>   /*      time/clock   */
#include <stdlib.h> /*      malloc, free */

#include "sort.h"   /* Sort functions API   */
#include "search.h" /* Search functions API */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *SET_GREEN_COLOR = "\033[0;32m";
static const char *SET_CYAN_COLOR = "\033[0;36m";
static const char *SET_BOLD_GREEN_COLOR =  "\033[1;32m";
static const char *SET_YELLOW_COLOR = "\033[0;33m";
static const char *RESET_COLOR = "\033[0m";

static const char print_str[] = "=============================================";
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

void SearchTest();

/* -Randomize values in array. */
static void ArrValueRandomizer(int *arr, 
                                size_t arr_size, 
                                int random_limit_upper,
                                int random_limit_lower);

/* -Print requsted array. */
static void PrintIntArr(int *arr, size_t arr_size);

/* -Create int array of size <size>.    */
int *CreateIntArray(int *arr, size_t size);

/* -<is_before_func>    */
int Isbefore(const void *data_1, const void *data_2, void *param);
/******************************************************************************/

int main()
{
    /* Use current time as seed for random generator */
    srand(time(NULL));

    SearchTest();

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

void SearchTest()
{
   static int *test_arr = 0;
   size_t arr_size = 15;
   int random_limit_upper = 1000000;
   int random_limit_lower = -1 * random_limit_upper;

    /* -Create test array & init it. */
    test_arr = CreateIntArray(test_arr, arr_size);
    ArrValueRandomizer(test_arr, arr_size, random_limit_upper, random_limit_lower);
    QuickSort(test_arr, arr_size, sizeof(int), &Isbefore);

    /* BinarySearch Test */
    printf("\n\t%s BinarySearch Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    PrintIntArr(test_arr, arr_size);
    puts(print_str);

}

static void ArrValueRandomizer(int *arr, 
                                size_t arr_size, 
                                int random_limit_upper,
                                int random_limit_lower)
{
    size_t i = 0;
    
    for(i = 0; i < arr_size; i++)
    {
        arr[i] = rand() % 
            (random_limit_upper + 1 - random_limit_lower) + random_limit_lower;
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

int *CreateIntArray(int *arr, size_t size)
{
    arr = (int *)malloc(sizeof(*arr) * size);
    if(NULL == arr)
    {
        return NULL;
    }

    return arr;
}

int Isbefore(const void *data_1, const void *data_2, void *param)
{
    (void)param;

    return *(int *)data_1 < *(int *)data_2;
}
/******************************************************************************/

