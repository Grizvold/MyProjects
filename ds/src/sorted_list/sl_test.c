#include <stddef.h> /*size_t  */
#include <stdlib.h> /* malloc, calloc, realloc, free, srand*/
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <time.h> /* time */

#include "sl.h"

void PrintAll(sl_t *sl);
void CompareListVal(sl_t *sl, int arr[]);
int IsBeforeInt(void *data1, void *data2, void *param);
int AddInt(void *data,  void *param);
int FindModulo(const void *data,  void *param);
int *CreateIntArray(size_t size);
void IntArrayToSl(sl_t *sl, int *arr, size_t size);


int num0 = 0;
int num1 = 1;
int num2 = 2;
int num3 = 3;
int num4 = 4;
int num5 = 5;
int int_to_add = 10;
int int_to_find_if = 4;
int int_to_find = 14;


int main()
{
	sl_t *sl_1 = NULL;
	sl_t *sl_2 = NULL;
	sl_t *sl_3 = NULL;
	sl_iter_t test_iter = {NULL};
	int i = 0;
	int *test_arr1 = NULL;
	int *test_arr2 = NULL; 


/* ############################### test no. 1 ############################### */
	sl_1 = SLCreate(&IsBeforeInt, NULL);

	printf("*** Insert test #1 ***\n");
	printf("is empty = %d\n", SLIsEmpty(sl_1));

	SLInsert(sl_1, &num3);
	SLInsert(sl_1, &num0);
	SLInsert(sl_1, &num1);
	SLInsert(sl_1, &num4);
	SLInsert(sl_1, &num2);

	printf("-After filling-\n");
	printf("is empty = %d\n", SLIsEmpty(sl_1));
	printf("size = %lu\n", SLSize(sl_1));
	PrintAll(sl_1);

/* ############################### test no. 2 ############################### */
	printf("\n*** Insert test #2 ***\n");
	printf("PopBack value = %d\n", *(int*)SLPopBack(sl_1));
	printf("PopFront value = %d\n", *(int*)SLPopFront(sl_1));
	printf("size = %lu\n", SLSize(sl_1));

	PrintAll(sl_1);

/*################################# ForEach ##################################*/
	printf("\n*** ForEach ***\nBefore:");

	SLInsert(sl_1, &num4);
	SLInsert(sl_1, &num0);
	SLInsert(sl_1, &num5);
	PrintAll(sl_1);

	SLForEach(SLBegin(sl_1), (SLEnd(sl_1)), &AddInt, &int_to_add);
	printf("After (values should be +=10):\n");
	PrintAll(sl_1);


/*################################# FindIf ###################################*/
	printf("\n*** FindIf ***\n");
	printf("FindIf Value (should be 12) = %d\n",
		   *(int*)SLIterGetData(
			SLFindIf(SLBegin(sl_1), (SLEnd(sl_1)), &FindModulo, &int_to_find_if)));


/*################################## Find ####################################*/
	printf("\n*** Find ***\n");
	printf("Find Value (should be 14) = %d\n",
		   *(int*)SLIterGetData(
			SLFind(SLBegin(sl_1), (SLEnd(sl_1)), &int_to_find)));

/*################################## Merge ###################################*/
	sl_2 = SLCreate(&IsBeforeInt, NULL);
	sl_3 = SLCreate(&IsBeforeInt, NULL);

	srand(time(NULL));
	test_arr1 = CreateIntArray(5);
	test_arr2 = CreateIntArray(5);

	IntArrayToSl(sl_2, test_arr1, 5);
	IntArrayToSl(sl_3, test_arr2, 5);

	printf("\n*** Merge ***\n");
	printf("Before:\n@@ sl_2\n");
	PrintAll(sl_2);
	printf("@@ sl_3\n");
	PrintAll(sl_3);

	SLMerge(sl_2, sl_3);

	printf("After:\n@@ sl_2\n");
	PrintAll(sl_2);
	printf("@@ sl_3\n");
	PrintAll(sl_3);

/* ################################# Remove ################################# */


	printf("\n*** Remove ***\n");
	test_iter = SLBegin(sl_1);
	SLRemove(test_iter);

	for (test_iter = SLBegin(sl_1), i = 0;
		 2 > i;
		 test_iter = SLIterNext(test_iter), i++)
	{
	}
	SLRemove(test_iter);

	test_iter = SLIterPrev(SLEnd(sl_1));
	SLRemove(test_iter);

	PrintAll(sl_1);



/* ################################ Destroy ################################# */


	SLDestroy(sl_1);
	sl_1 = NULL;
	SLDestroy(sl_2);
	sl_2 = NULL;
	SLDestroy(sl_3);
	sl_3 = NULL;

/* Clean Up to Test Arrays  */
	free(test_arr1);
	free(test_arr2);

	return 0;
}



int IsBeforeInt(void *data1, void *data2, void *param)
{
	assert(NULL != data1);
	assert(NULL != data2);

	(void)param;

	return ((*(int*)data1 - *(int*)data2) < 0);
}

void PrintAll(sl_t *sl)
{
	sl_iter_t print_iter =  {NULL};
	void *temp_data = NULL;
	
	for (print_iter = SLBegin(sl);
		 ! SLIterIsEqual(print_iter, SLEnd(sl));
		 print_iter = SLIterNext(print_iter))
	{
		temp_data = SLIterGetData(print_iter);
		printf("\tdata = %d\n", *(int*)temp_data);
	}
}


void CompareListVal(sl_t *sl, int arr[])
{
	sl_iter_t cmp_iter =  {NULL};
	void *temp_data = NULL;
	int i = 0;
	
	for (cmp_iter = SLBegin(sl), i = 0;
		 ! SLIterIsEqual(cmp_iter, SLEnd(sl));
		 cmp_iter = SLIterNext(cmp_iter), i++)
	{
		temp_data = SLIterGetData(cmp_iter);
		if (*((int*)temp_data) == arr[i])
		{
			printf("\tnode no. %d - SUCCSESS\n", i);
		}
		else
		{
			printf("\tnode no. %d - FAIL\n", i);
		}
	}
}


int AddInt(void *data,  void *param)
{
	int is_success = 0;

	*(int*)data += *(int*)param;

	return is_success;
}



int FindModulo(const void *data,  void *param)
{
	return ((*(int*)data % *(int*)param) == 0) ? 1 : 0;
}

int *CreateIntArray(size_t size)
{
	int *arr = NULL;
	
	arr = (int*)malloc(sizeof(*arr) * size);
	if (NULL == arr)
	{
		return NULL;
	}
	

	for (; 0 < size; size--)
	{
		arr[size-1] = rand() % 20;	
	}

	return arr;
}

void IntArrayToSl(sl_t *sl, int *arr, size_t size)
{
	size_t i = 0;
	
	for (i = 0; size > i; i++)
	{
		SLInsert(sl, arr + i);
	}
}




