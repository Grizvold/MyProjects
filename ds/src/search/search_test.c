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
static const char *SET_CYAN_COLOR = "\033[0;36m";
static const char *RESET_COLOR = "\033[0m";

static clock_t start_time = 0;
static clock_t end_time = 0;
static double cpu_time_used = 0;
/******************************************************************************/

/******************************************************************************/
/*                          Test Function Declaration                         */
/******************************************************************************/

/* -Main test function. */
static void SearchTest();

/* -Binary search test function. */
static void SearchBinaryRecTest(int *test_arr, size_t arr_size, int key_value);

/* -Iterative search test function. */
static void SearchBinaryIterTest(int *test_arr, size_t arr_size, int key_value);

/* -Jump search test function. */
static void SearchJumpIterTest(int *test_arr, size_t arr_size, int key_value);
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

/* -Randomize values in array. */
static void ArrValueRandomizer(int *arr,
                               size_t arr_size,
                               int random_limit_upper,
                               int random_limit_lower);

/* -Get random element from int array. */
static int GetRandomElement(int *test_array, size_t arr_size);

/* -Print requsted array. */
static void PrintIntArr(int *arr, size_t arr_size);

/* -Create int array of size <size>.    */
int *CreateIntArray(int *arr, size_t size);

/* -<is_before_func>    */
int Isbefore(const void *data_1, const void *data_2, void *param);

/* -<cmp_func>          */
int IntCmp(const void *data_1, const void *data_2);
/******************************************************************************/

int main()
{
    /* Use current time as seed for random generator */
    srand(time(NULL));

    SearchTest();

    return 0;
}

/******************************************************************************/
/*                          Test Function Definition                         */
/******************************************************************************/

static void SearchTest()
{
    static int *test_arr = 0;
    size_t arr_size = 50000;
    int random_limit_upper = 1000000;
    int random_limit_lower = -1 * random_limit_upper;

    /* -Create test array & init it. */
    test_arr = CreateIntArray(test_arr, arr_size);
    ArrValueRandomizer(test_arr, arr_size, random_limit_upper, random_limit_lower);
    QuickSort(test_arr, arr_size, sizeof(int), &Isbefore);
    PrintIntArr(test_arr, arr_size);

    /* Binary_Recursive_Search Test */
    printf("\n\t%s Binary Recursive Search Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    SearchBinaryRecTest(test_arr, arr_size, GetRandomElement(test_arr, arr_size));

    /* Binary_Iterative_Search Test */
    printf("\n\t%s Binary Iterative Search Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    SearchBinaryIterTest(test_arr, arr_size, GetRandomElement(test_arr, arr_size));

    /* Jump_Iterative_Search Test */
    printf("\n\t%s Jump Iterative Search Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    SearchJumpIterTest(test_arr, arr_size, GetRandomElement(test_arr, arr_size));
}

static void SearchBinaryRecTest(int *test_arr, size_t arr_size, int key_value)
{
    void *search_result = NULL;

    start_time = clock();
    printf("Requested value to find: %s%d%s\n", SET_BLUE_COLOR, key_value, RESET_COLOR);
    search_result = BinarySearchRec(test_arr,
                                    arr_size,
                                    sizeof(int),
                                    &key_value,
                                    &IntCmp);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Found value: %s%d%s\n", SET_BLUE_COLOR, key_value, RESET_COLOR);
    printf("\nTime taken by process: %f\n", cpu_time_used);

    (key_value == *(int *)search_result) ? 
            printf("\n\t%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) : 
            printf("\n\t%s FAILURE Line number:%d%s\n", SET_RED_COLOR, 
                                                        __LINE__, 
                                                        RESET_COLOR);
}

static void SearchBinaryIterTest(int *test_arr, size_t arr_size, int key_value)
{
    void *search_result = NULL;

    start_time = clock();
    printf("Requested value to find: %s%d%s\n", SET_BLUE_COLOR, key_value, RESET_COLOR);
    search_result = BinarySearchIter(test_arr,
                                     arr_size,
                                     sizeof(int),
                                     &key_value,
                                     &IntCmp);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Found value: %s%d%s\n", SET_BLUE_COLOR, key_value, RESET_COLOR);
    printf("\nTime taken by process: %f\n", cpu_time_used);

    (key_value == *(int *)search_result) ? 
            printf("\n\t%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) : 
            printf("\n\t%s FAILURE Line number:%d%s\n", SET_RED_COLOR, 
                                                        __LINE__, 
                                                        RESET_COLOR);
}

static void SearchJumpIterTest(int *test_arr, size_t arr_size, int key_value)
{
    void *search_result = NULL;

    start_time = clock();
    printf("Requested value to find: %s%d%s\n", SET_BLUE_COLOR, key_value, RESET_COLOR);
    search_result = JumpSearchIter(test_arr,
                                     arr_size,
                                     sizeof(int),
                                     &key_value,
                                     &IntCmp);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Found value: %s%d%s\n", SET_BLUE_COLOR, key_value, RESET_COLOR);
    printf("\nTime taken by process: %f\n", cpu_time_used);

    (key_value == *(int *)search_result) ? 
            printf("\n\t%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) : 
            printf("\n\t%s FAILURE Line number:%d%s\n", SET_RED_COLOR, 
                                                        __LINE__, 
                                                        RESET_COLOR);
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void ArrValueRandomizer(int *arr,
                               size_t arr_size,
                               int random_limit_upper,
                               int random_limit_lower)
{
    size_t i = 0;

    for (i = 0; i < arr_size; i++)
    {
        arr[i] = rand() %
                     (random_limit_upper + 1 - random_limit_lower) +
                 random_limit_lower;
    }
}

static int GetRandomElement(int *test_array, size_t arr_size)
{
    size_t key_index = 0;
    int key_value = 0;

    key_index = 1 + rand() % (arr_size - 2);
    key_value = test_array[key_index];

    return key_value;
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
    if (NULL == arr)
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

int IntCmp(const void *data_1, const void *data_2)
{
    int num_1 = 0;
    int num_2 = 0;

    num_1 = *(int *)data_1;
    num_2 = *(int *)data_2;

    return num_1 - num_2;
}
/******************************************************************************/
