#include <stddef.h> /* size_t             */
#include <stdio.h>  /* printf             */
#include <stdlib.h> /* malloc, free, rand */
#include <string.h> /* strcpy			  */
#include <time.h>   /* time               */

#include "search.h"   /* searching algorithms API */
#include "sort.h"   /* sorting algorithms API */


#define SIZE 50001

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define MAGNETA "\033[1;35m"
#define BLUE "\033[1;36m"
#define NRM "\033[0m"


/* ####################################### Typedef & Enums ###################################### */
typedef enum {BINARY_REC = 0, BINARY_ITER = 1, JUMP = 2} search_name_t;
typedef void *(*search_func_t)(void *arr, size_t n_members, size_t member_size, void *key,
			  				   cmp_func_t func);


/* #################################### Functions Declarations ################################## */
/* test functions */
void TestIntSearch(int *arr, size_t arr_size, int num_not_in_arr, cmp_func_t cmp_func, 
					search_name_t search_name);
void SingleTestIntSearch(int *arr, size_t arr_size, int num_not_in_arr, cmp_func_t cmp_func, 
						search_func_t search_func, char *search_name);
void TestJumpSearch(int *arr, size_t arr_size, int num_not_in_arr, cmp_func_t cmp_func,
				    size_t max_rec_calls);

/* cmp & is_before functions */
int IntCmp(const void *key1, const void *key2);
int IntIsBefore(const void *member1, const void *member2, void *param);

/* int array functions */
int *IntArrCreateRandom(size_t size, int low_bound, int high_bound);


/* ################################## Global & Static Variables ################################# */
int low_limit = 0;
int high_limit = 0;

/* ############################################ Main ############################################ */
int main()
{
    int *test_arr1 = NULL;
	int num_not_in_test_arr = 0;
	int max_rec_calls = 0;

    srand(time(NULL));

	/* setting the range of integers in the test array (both positive & positive) */
    high_limit = 1000000;
    low_limit = high_limit * -1;
	num_not_in_test_arr = high_limit + 1;

	/* creating a sorted random int array */
	test_arr1 = IntArrCreateRandom(SIZE, low_limit, high_limit);
	QuickSort(test_arr1, SIZE, sizeof(test_arr1[0]), &IntIsBefore, NULL);

	/* testing binary search functions */
	TestIntSearch(test_arr1, SIZE, num_not_in_test_arr, &IntCmp, BINARY_REC);
	TestIntSearch(test_arr1, SIZE, num_not_in_test_arr, &IntCmp, BINARY_ITER);

	/* testing jump search */
	max_rec_calls = 7; /* don't put 1 here, because the test already checks that inside */
	TestJumpSearch(test_arr1, SIZE, num_not_in_test_arr, &IntCmp, max_rec_calls);

    free(test_arr1);
    test_arr1 = NULL;

    return 0;
}

/* ################################### Functions Definitions #################################### */
/* ********************************************************************************************** */
/*                                        Test Functions                                          */
/* ********************************************************************************************** */
void TestIntSearch(int *arr, size_t arr_size, int num_not_in_arr, cmp_func_t cmp_func, 
					search_name_t search_name)
{
	static search_func_t search_func_LUT[3] = {NULL};
	static char search_name_LUT[3][30] = {""};

	/* initialize the LUTs, if neccasery */
	if (NULL == search_func_LUT[0])
	{
		search_func_LUT[0] = &BinarySearchRec;
		search_func_LUT[1] = &BinarySearchIter;
		/*search_func_LUT[2] = &JumpSearchIter;*/

		strcpy(search_name_LUT[0], "Binary Search - Recursive");
		strcpy(search_name_LUT[1], "Binary Search - Iterative");
		/*strcpy(search_name_LUT[2], "Jump Search");*/
	}

	SingleTestIntSearch(arr, arr_size, num_not_in_arr, cmp_func, search_func_LUT[search_name],
							 search_name_LUT[search_name]);
}

/* test one search function */
void SingleTestIntSearch(int *arr, size_t arr_size, int num_not_in_arr, cmp_func_t cmp_func, 
						search_func_t search_func, char *search_name)
{
	void *search_result = NULL;
	int num_to_find;
	size_t index = 0;

    printf("\n%s******************* %s ******************%s\n", YELLOW, search_name, NRM);
	
	/* test 1 - find a random number from the array (except the 1st or last) */
	index = 1 + rand() % (arr_size - 2);
	num_to_find = arr[index];

	printf("find the number %s%d%s located in index %s%lu%s of the array - ", 
			BLUE, num_to_find, NRM, MAGNETA, index, NRM);

	search_result = search_func(arr, arr_size, sizeof(arr[0]), &num_to_find, cmp_func);

    switch (num_to_find == *(int*)search_result) 
    {
    case 1:
        printf("%sSUCCESS%s\n", GREEN, NRM);
        break;
    case 0:
        printf("%sFAILURE%s\n", RED, NRM);
        break;
    }
	/* end of test 1 */

	/* test 2 - find the 1st number of the array */
	num_to_find = arr[0];
	printf("find the number %s%d%s located in the %s1st%s index of the array - ", 
			BLUE, num_to_find, NRM, MAGNETA, NRM);
	search_result = search_func(arr, arr_size, sizeof(arr[0]), &num_to_find, cmp_func);

    switch (num_to_find == *(int*)search_result) 
    {
    case 1:
        printf("%sSUCCESS%s\n", GREEN, NRM);
        break;
    case 0:
        printf("%sFAILURE%s\n", RED, NRM);
        break;
    }
	/* end of test 2 */

	/* test 3 - find the last number from the array */
	num_to_find = arr[arr_size - 1];
	printf("find the number %s%d%s located in the %slast%s index of the array - ", 
			BLUE, num_to_find, NRM, MAGNETA, NRM);
	search_result = search_func(arr, arr_size, sizeof(arr[0]), &num_to_find, cmp_func);

    switch (num_to_find == *(int*)search_result) 
    {
    case 1:
        printf("%sSUCCESS%s\n", GREEN, NRM);
        break;
    case 0:
        printf("%sFAILURE%s\n", RED, NRM);
        break;
    }
	/* end of test 3 */

	/* test 4 - return NULL for a number not in the array */
    printf("return %sNULL%s for number not in the array - ", BLUE, NRM);
	search_result = search_func(arr, arr_size, sizeof(arr[0]), &num_not_in_arr, cmp_func);

    switch (NULL == search_result) 
    {
    case 1:
        printf("%sSUCCESS%s\n", GREEN, NRM);
        break;
    case 0:
        printf("%sFAILURE%s\n", RED, NRM);
        break;
    }
	/* end of test 4 */

}


/* ********************************************************************************************** */
/*                                  	 Jump Search Test                                         */
/* ********************************************************************************************** */
void TestJumpSearch(int *arr, size_t arr_size, int num_not_in_arr, cmp_func_t cmp_func,
				    size_t max_rec_calls)
{
	void *search_result = NULL;
	int num_to_find;
	size_t index = 0;
	size_t i = 0;
	size_t max_calls[2] = {0};

    printf("\n%s************************** Jump Search *************************%s\n", YELLOW, NRM);
	
	max_calls[0] = max_rec_calls;
	max_calls[1] = 1;

	for (i = 0; 2 > i; i++)
	{
		printf("\n%sTesting for max_rec_calls = %lu :%s\n", MAGNETA, max_calls[i], NRM);

		/* test 1 - find a random number from the array (except the 1st or last) */
		index = 1 + rand() % (arr_size - 2);
		num_to_find = arr[index];

		printf("find the number %s%d%s located in index %s%lu%s of the array - ", 
				BLUE, num_to_find, NRM, MAGNETA, index, NRM);

		search_result = JumpSearch(arr, arr_size, sizeof(arr[0]), &num_to_find, cmp_func,
								   max_calls[i]);

		switch (num_to_find == *(int*)search_result) 
		{
		case 1:
			printf("%sSUCCESS%s\n", GREEN, NRM);
			break;
		case 0:
			printf("%sFAILURE%s\n", RED, NRM);
			break;
		}
		/* end of test 1 */

		/* test 2 - find the 1st number of the array */
		num_to_find = arr[0];
		printf("find the number %s%d%s located in the %s1st%s index of the array - ", 
				BLUE, num_to_find, NRM, MAGNETA, NRM);
		search_result = JumpSearch(arr, arr_size, sizeof(arr[0]), &num_to_find, cmp_func,
								   max_calls[i]);

		switch (num_to_find == *(int*)search_result) 
		{
		case 1:
			printf("%sSUCCESS%s\n", GREEN, NRM);
			break;
		case 0:
			printf("%sFAILURE%s\n", RED, NRM);
			break;
		}
		/* end of test 2 */

		/* test 3 - find the last number from the array */
		num_to_find = arr[arr_size - 1];
		printf("find the number %s%d%s located in the %slast%s index of the array - ", 
				BLUE, num_to_find, NRM, MAGNETA, NRM);
		search_result = JumpSearch(arr, arr_size, sizeof(arr[0]), &num_to_find, cmp_func,
								   max_calls[i]);

		switch (num_to_find == *(int*)search_result) 
		{
		case 1:
			printf("%sSUCCESS%s\n", GREEN, NRM);
			break;
		case 0:
			printf("%sFAILURE%s\n", RED, NRM);
			break;
		}
		/* end of test 3 */

		/* test 4 - return NULL for a number not in the array */
		printf("return %sNULL%s for number not in the array - ", BLUE, NRM);
		search_result = JumpSearch(arr, arr_size, sizeof(arr[0]), &num_not_in_arr, cmp_func,
								   max_calls[i]);

		switch (NULL == search_result) 
		{
		case 1:
			printf("%sSUCCESS%s\n", GREEN, NRM);
			break;
		case 0:
			printf("%sFAILURE%s\n", RED, NRM);
			break;
		}
		/* end of test 4 */
	}

}


/* ********************************************************************************************** */
/*                                  CMP & Is_Before Functions                                     */
/* ********************************************************************************************** */
int IntCmp(const void *key1, const void *key2)
{
	int num1 = 0;
	int num2 = 0;

	num1 = *(int*)key1;
	num2 = *(int*)key2;

	return num1 - num2; 
}

int IntIsBefore(const void *member1, const void *member2, void *param)
{
	(void)param;

	return *(int*)member1 < *(int*)member2; 
}


/* ********************************************************************************************** */
/*                                      Int Array Functions                                       */
/* ********************************************************************************************** */
int *IntArrCreateRandom(size_t size, int low_bound, int high_bound)
{
	int *arr = NULL;
	
	arr = (int*)malloc(sizeof(*arr) * size);
	if (NULL == arr)
	{
		return NULL;
	}

	for (; 0 < size; size--)
	{
		arr[size-1] = rand() % (high_bound - low_bound) + low_bound;
	}

	return arr;
}