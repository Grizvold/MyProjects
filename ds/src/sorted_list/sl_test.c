#include <stdio.h>  /*printf */
#include <stdlib.h> /*malloc*/

#include "dll.h"
#include "sl.h"

int Add(void* data, void* param);

/* returns 1 if same data
 		 0 not same data		   	*/
int Find(const void* data, void* cmp);

/* returns 1 if <newdata> < <cmpdata>
		 0 if <newdata> > <cmpdata> 	*/
int IsBefore(void *newdata, void* cmpdata, void *param);

int Print(void *data, void *param);

int main()
{
	sl_t *my_sl = NULL;
	sl_t *new_sl = NULL;
	
	sl_iter_t iter;
	
	int *arr = NULL;

	int A = 3;
	int B = 9;
	int C = 2;
	int E = 4;
	size_t i = 0;
	
	arr = malloc((sizeof(int)) * 9);
	if (NULL == arr)
	{
		return 1;
	}
	
	arr[0] = 5;
	arr[1] = 6;
	arr[2] = 7;
	arr[3] = 2;
	arr[4] = 9;
	arr[5] = 6;
	arr[6] = 7;
	arr[7] = 2;
	arr[8] = 9;
	
	my_sl = SLCreate(&IsBefore, NULL);
	new_sl = SLCreate(&IsBefore, NULL);
	
	printf("\ntest SLIsEmpty:\n");
	(SLIsEmpty(my_sl) == 1) ? printf("success\n") : printf("failure\n");
	(SLIsEmpty(new_sl) == 1) ? printf("success\n") : printf("failure\n");

	for (i = 0; i<5; i++)
	{
		SLInsert(my_sl, &arr[i]);
	}
	
	for (i = 0; i<9; i++)
	{
		SLInsert(new_sl, &arr[i]);
	}
	
	(SLIsEmpty(my_sl) == 0) ? printf("success\n") : printf("failure\n");
	
	printf("\ntest SLSize:\n");
	(SLSize(my_sl) == 5) ? printf("success\n") : printf("failure\n");
	(SLSize(new_sl) == 9) ? printf("success\n") : printf("failure\n");
		
	printf("\ntesting insert- printing fisrt list (5 first elements)list:\n");
	SLForEach(SLBegin(my_sl), SLEnd(my_sl), &Print, NULL);
	printf("\ntesting insert- printing second second (4 last elements)list :\n");
	SLForEach(SLBegin(new_sl), SLEnd(new_sl), &Print, NULL);
	
	printf("\n\ntest SLPopFront first list\n");
	SLPopFront(my_sl);
	SLForEach(SLBegin(my_sl), SLEnd(my_sl), &Print, NULL);
	/*printf("\n");
	SLPopFront(new_sl);
	SLForEach(SLBegin(new_sl), SLEnd(new_sl), &Print, NULL);*/
	
	printf("\n\ntest SLPopBack first list\n");
	SLPopBack(my_sl);
	SLForEach(SLBegin(my_sl), SLEnd(my_sl), &Print, NULL);
	
	printf("\n\ntest SLIterNext for first list\n");
	(*(int *)SLIterGetData(SLIterNext(SLBegin(my_sl))) == 6) ? printf("success\n") : printf("failure\n");

	printf("\ntest SLIterPrev and DLLEnd\n");
	iter = SLIterPrev(SLEnd(my_sl));
	(*(int *)SLIterGetData(iter) == 7) ? printf("success\n") : printf("failure\n");

	printf("\ntest SLForEach\n");
	printf("adding 2 to first list, original list:\n");
	SLForEach(SLBegin(my_sl), SLEnd(my_sl), &Print, NULL);
	SLForEach(SLBegin(my_sl), SLEnd(my_sl), &Add, &C);
	printf("\nafter adding operation:\n");
	SLForEach(SLBegin(my_sl), SLEnd(my_sl), &Print, NULL);
	
	printf("\n\ntest SLFind\n");
	printf("find 9 in list\n");
	iter = SLFind(SLBegin(my_sl), SLEnd(my_sl), &B); 
	(*(int *)SLIterGetData(iter) == 9) ? printf("success\n") : printf("failure\n");	
	printf("found element %d\n", (*(int *)SLIterGetData(iter)));
	
	printf("\ntest SLFindIf\n");
	iter = SLFindIf(SLBegin(my_sl), SLEnd(my_sl), &Find, &A); 
	(*(int *)SLIterGetData(iter) == 9) ? printf("success\n") : printf("failure\n");

	printf("\ntest SLRemove\n");			
	SLRemove(SLIterNext(SLBegin(my_sl)));
	(*(int *)SLIterGetData(SLIterNext(SLBegin(my_sl))) == 9) ? printf("success\n") : printf("failure\n"); 
	
	SLForEach(SLBegin(new_sl), SLEnd(new_sl), &Add, &E);
	printf("\ntestin SLMerge\n");
	printf("\nsrc list: \n");
	SLForEach(SLBegin(my_sl), SLEnd(my_sl), &Print, NULL);
	printf("\ndest list: \n");
	SLForEach(SLBegin(new_sl), SLEnd(new_sl), &Print, NULL);
	
	SLMerge(my_sl, new_sl);
	printf("\nmerged list: \n");
	SLForEach(SLBegin(my_sl), SLEnd(my_sl), &Print, NULL);
	
	printf("\nsrc list: \n");
	SLForEach(SLBegin(new_sl), SLEnd(new_sl), &Print, NULL);
	printf("\n"); 
	
	while (!SLIsEmpty(my_sl))
	{
		SLPopFront(my_sl);
	}
	
	SLDestroy(my_sl);
	SLDestroy(new_sl);
	free(arr);
	
	return 0;
}


int Add(void* data, void* param)
{
	*(int *)data += *(int *)param;
	
	return 0;
}

int Find(const void* data, void* cmp)
{
	return (*(int *)data % *(int *)cmp == 0);
}

int IsBefore(void *newdata, void *cmpdata, void *param)
{
	(void)param;
	return   ((*(int *)newdata - *(int *)cmpdata) < 0);
}

int Print(void *data, void *param)
{
	printf("%d ", *(int *)data);
	
	(void)param;
	
	return 0;
}





