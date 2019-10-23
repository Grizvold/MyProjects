#include <stdio.h>  /* printf */
#include <stdlib.h> /*malooc */

#include "dll.h"

/* adds the <param> to the <data */
int Add(void* data, void* param);
/* compers the <data> to <cmp>
	returns 1 if they are equal, 0 if they are not */
int Find(const void* data, void* cmp);

int main()
{
	dll_t *my_dll = NULL;
	dll_t *new_dll = NULL;
	dll_t *empty_dll = NULL;
	
	dll_iter_t iter;
	
	int *arr = NULL;
	int *newarr = NULL;
	
	int A = 2;
	int B = 9;
	int C = 100;
	size_t i = 0;
	
	arr = malloc(sizeof(int)*5);
	if (NULL == arr)
	{
		return 1;
	}
	
	arr[0] = 5;
	arr[1] = 6;
	arr[2] = 7;
	arr[3] = 2;
	arr[4] = 9;
	
	newarr = malloc(sizeof(int)*4);
	if (NULL == newarr)
	{
		return 1;
	}
	
	newarr[0] = 5;
	newarr[1] = 6;
	newarr[2] = 7;
	newarr[3] = 8;
	
	my_dll = DLLCreate();
	new_dll = DLLCreate();
	empty_dll = DLLCreate();
	
	
	for (i=0; i<3; i++)
	{
		DLLPushFront(my_dll, &arr[i]);
	}
	
	printf("\ntest DLLIsEmpty:\n");
	(DLLIsEmpty(my_dll) == 0) ? printf("success\n") : printf("failure\n");
	(DLLIsEmpty(new_dll) != 0) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLSize:\n");
	(DLLSize(my_dll) == 3) ? printf("success\n") : printf("failure\n");
	(DLLSize(new_dll) == 0) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLIterGetData and DLLBegin:\n");
	(*(int *)DLLIterGetData(DLLBegin(my_dll)) == 7) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLPushFront\n");
	DLLPushFront(my_dll,&arr[3]);
	(*(int *)DLLIterGetData(DLLBegin(my_dll)) == 2) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLPopFront\n");
	DLLPopFront(my_dll);
	(*(int *)DLLIterGetData(DLLBegin(my_dll)) == 7) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLPushBack\n");
	DLLPushBack(my_dll,&arr[2]);
	(*(int *)DLLIterGetData(DLLIterPrev(DLLEnd(my_dll))) == 7) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLPopBack\n");
	DLLPopBack(my_dll);
	(*(int *)DLLIterGetData(DLLIterPrev(DLLEnd(my_dll))) == 5) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLIterNext\n");
	iter = DLLIterNext(DLLBegin(my_dll));
	(*(int *)DLLIterGetData(iter) == 6) ? printf("success\n") : printf("failure\n");

	printf("\ntest DLLIterPrev and DLLEnd\n");
	iter = DLLIterPrev(DLLEnd(my_dll));
	(*(int *)DLLIterGetData(iter) == 5) ? printf("success\n") : printf("failure\n");

	printf("\ntest DLLForEach\n");
	DLLForEach(DLLBegin(my_dll), DLLEnd(my_dll), &Add, &A);
	iter =  DLLBegin(my_dll);
	((*(int *)DLLIterGetData(iter) == 9) && (*(int *)DLLIterGetData(DLLIterNext(iter)) == 8)) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLFind\n");
	iter = DLLFind(DLLBegin(my_dll), DLLEnd(my_dll), &Find, &B); 
	(*(int *)DLLIterGetData(iter) == 9) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest DLLInsert\n");			
	DLLInsert(DLLBegin(my_dll), &arr[3]);
	(*(int *)DLLIterGetData(DLLBegin(my_dll)) == 2) ? printf("success\n") : printf("failure\n"); 
	
	DLLInsert(DLLIterNext(DLLBegin(my_dll)), &arr[4]);
	(*(int *)DLLIterGetData(DLLIterNext(DLLBegin(my_dll))) == 9) ? printf("success\n") : printf("failure\n"); 
	
	printf("\ntest DLLRemove\n");			
	DLLRemove(DLLBegin(my_dll));
	(*(int *)DLLIterGetData(DLLBegin(my_dll)) == 9) ? printf("success\n") : printf("failure\n"); 
	
	DLLRemove(DLLIterNext(DLLBegin(my_dll)));
	(*(int *)DLLIterGetData(DLLIterNext(DLLBegin(my_dll))) == 8) ? printf("success\n") : printf("failure\n"); 

	printf("\ntest DLLSplice\n");
	
	for (i=0; i<4; i++)
	{
		DLLPushBack(new_dll, &newarr[i]);
	}	
	
	DLLForEach(DLLBegin(new_dll), DLLEnd(new_dll), &Add, &C);
	
	printf("First list:\n");
	for(iter = DLLBegin(new_dll); !DLLIterIsEqual(iter, DLLEnd(new_dll)); iter = DLLIterNext(iter))
	{
		printf("%d\n", *(int *)DLLIterGetData(iter));
	}
		
	printf("\nSecond list:\n");
	for(iter = DLLBegin(my_dll); !DLLIterIsEqual(iter, DLLEnd(my_dll)); iter = DLLIterNext(iter))
	{
		printf("%d\n", *(int *)DLLIterGetData(iter));
	}
	
	DLLSplice(DLLIterNext(DLLBegin(my_dll)),DLLBegin(new_dll),  DLLEnd(new_dll));
	
	printf("src list:\n");
	for(iter = DLLBegin(new_dll); !DLLIterIsEqual(iter, DLLEnd(new_dll)); iter = DLLIterNext(iter))
	{
		printf("%d\n", *(int *)DLLIterGetData(iter));
	}
		
	printf("\ndest list:\n");
	for(iter = DLLBegin(my_dll); !DLLIterIsEqual(iter, DLLEnd(my_dll)); iter = DLLIterNext(iter))
	{
		printf("%d\n", *(int *)DLLIterGetData(iter));
	}

	printf("\nempty list:\n");
	for(iter = DLLBegin(empty_dll); !DLLIterIsEqual(iter, DLLEnd(empty_dll)); iter = DLLIterNext(iter))
	{
		printf("%d\n", *(int *)DLLIterGetData(iter));
	}
	
	DLLDestroy(my_dll);
	DLLDestroy(new_dll);
	DLLDestroy(empty_dll);
	
	free(arr);
	free(newarr);
	
	return 0;
}


int Add(void* data, void* param)
{
	*(int *)data += *(int *)param;
	
	return 0;
}

int Find(const void* data, void* cmp)
{
	return (*(int *)data == *(int *)cmp);
}





