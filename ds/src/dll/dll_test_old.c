#include <stddef.h> /* size_t 							 */
#include <stdio.h>  /* printf 							 */

#include "dll.h" 	/* declarations of the dll functions */

/************************ Test Functions Declarations *************************/
void PrintAll(dll_t *dll);
void CompareListVal(dll_t *dll, int arr[]);

/************************* Test Variables Defenitions *************************/
int test_arr[10] = {0, 1, 2, 3, 4};

/******************************* Main *****************************************/
int main()
{
	int num0 = 0;
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num10 = 10;
	int num11 = 11;
	int num12 = 12;
	int num13 = 13;
	int i = 0;

	dll_t *dll_1 = NULL, *dll_2 = NULL;
	dll_iter_t test_iter1 = {NULL, NULL};
	dll_iter_t test_iter_from = {NULL, NULL}, test_iter_to = {NULL, NULL};

/* ############### Create, PushBack, PushFront, IsEmpty, Size ############### */
	dll_1 = DLLCreate();

	printf("*** test #1 ***\n");
	printf("\n*** Pop ***\n");
	printf("is empty = %d\n", DLLIsEmpty(dll_1));

	DLLPushBack(dll_1, &num1);
	DLLPushBack(dll_1, &num2);
	DLLPushBack(dll_1, &num3);
	DLLPushBack(dll_1, &num4);
	DLLPushFront(dll_1, &num0);

	printf("-After filling-\n");
	printf("is empty = %d\n", DLLIsEmpty(dll_1));
	printf("size = %lu\n", DLLSize(dll_1));
	CompareListVal(dll_1, test_arr);

/* ########################### PopBack, PopFront ############################ */
	printf("\n*** PopBack & PopFront - test #1 ***\n");
	printf("PopBack value = %d\n", *(int*)DLLPopBack(dll_1));
	printf("PopFront value = %d\n", *(int*)DLLPopFront(dll_1));
	printf("size = %lu\n", DLLSize(dll_1));

	test_arr[0] = 1;
	test_arr[1] = 2;
	test_arr[2] = 3;
	CompareListVal(dll_1, test_arr);

	DLLPopBack(dll_1);
	DLLPopFront(dll_1);

	test_arr[0] = 2;
	printf("\n*** PopBack & PopFront - test #2 ***\n");
	CompareListVal(dll_1, test_arr);

/* ################################## Push ################################## */
	DLLDestroy(dll_1);
	dll_1 = NULL;
	dll_1 = DLLCreate();

	DLLPushFront(dll_1, &num3);
	DLLPushBack(dll_1, &num4);
	DLLPushFront(dll_1, &num2);
	DLLPushFront(dll_1, &num1);
	DLLPushFront(dll_1, &num0);

	test_arr[0] = 0;
	test_arr[1] = 1;
	test_arr[2] = 2;
	test_arr[3] = 3;
	test_arr[4] = 4;
	printf("\n*** Push ***\n");
	CompareListVal(dll_1, test_arr);

/* ################################# Insert ################################# */
	test_iter1 = DLLBegin(dll_1);
	DLLInsert(test_iter1, &num5);

	for (test_iter1 = DLLBegin(dll_1), i = 0;
		 3 > i;
		 test_iter1 = DLLIterNext(test_iter1), i++)
	{
	}
	DLLInsert(test_iter1, &num5);

	test_iter1 = (DLLEnd(dll_1));
	DLLInsert(test_iter1, &num5);

	test_arr[0] = 5;
	test_arr[1] = 0;
	test_arr[2] = 1;
	test_arr[3] = 5;
	test_arr[4] = 2;
	test_arr[5] = 3;
	test_arr[6] = 4;
	test_arr[7] = 5;
	printf("\n*** Insert ***\n");
	CompareListVal(dll_1, test_arr);

/* ################################# Remove ################################# */
	test_iter1 = DLLBegin(dll_1);
	DLLRemove(test_iter1);

	for (test_iter1 = DLLBegin(dll_1), i = 0;
		 2 > i;
		 test_iter1 = DLLIterNext(test_iter1), i++)
	{
	}

	DLLRemove(test_iter1);

	test_iter1 = DLLIterPrev(DLLEnd(dll_1));
	DLLRemove(test_iter1);

	test_arr[0] = 0;
	test_arr[1] = 1;
	test_arr[2] = 2;
	test_arr[3] = 3;
	test_arr[4] = 4;
	printf("\n*** Remove ***\n");
	CompareListVal(dll_1, test_arr);

/* ################################# Splice ################################# */
	dll_2 = DLLCreate();

	DLLPushBack(dll_2, &num10);
	DLLPushBack(dll_2, &num11);
	DLLPushBack(dll_2, &num12);
	DLLPushBack(dll_2, &num13);

	test_iter1 = DLLIterNext(DLLBegin(dll_1));
	test_iter_from = DLLIterNext(DLLBegin(dll_2));
	test_iter_to = DLLIterNext(test_iter_from);

	DLLSplice(test_iter1, test_iter_from, test_iter_to);

	printf("\n*** Splice ***\n");
	printf("\tdll_1:\n");
	PrintAll(dll_1);

	printf("\tdll_2:\n");
	PrintAll(dll_2);

	test_iter_from = test_iter_to = DLLIterNext(DLLBegin(dll_2));
	DLLSplice(test_iter1, test_iter_from, test_iter_to);
	printf("\n\tdll_1:\n");
	PrintAll(dll_1);

	printf("\tdll_2:\n");
	PrintAll(dll_2);
	 
/* ################################# Destroy ################################# */
	DLLDestroy(dll_1);
	dll_1 = NULL;

	DLLDestroy(dll_2);
	dll_2 = NULL;

	return 0;
}

/************************* Test Functions Defenitions *************************/
void PrintAll(dll_t *dll)
{
	dll_iter_t print_iter =  {NULL, NULL};
	void *temp_data = NULL;
	
	for (print_iter = DLLBegin(dll);
		 ! DLLIterIsEqual(print_iter, DLLEnd(dll));
		 print_iter = DLLIterNext(print_iter))
	{
		temp_data = DLLIterGetData(print_iter);
		printf("data = %d\n", *(int*)temp_data);
	}
}

void CompareListVal(dll_t *dll, int arr[])
{
	dll_iter_t cmp_iter =  {NULL, NULL};
	void *temp_data = NULL;
	int i = 0;
	
	for (cmp_iter = DLLBegin(dll), i = 0;
		 !DLLIterIsEqual(cmp_iter, DLLEnd(dll));
		 cmp_iter = DLLIterNext(cmp_iter), i++)
	{
		temp_data = DLLIterGetData(cmp_iter);
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


