#include <stdio.h> /* printf */

#include "pq_heap.h"

typedef struct student
{
	char *name;
	int id;
}student_t;

int IsBefore(const void *newdata, const void* cmpdata, void *param);
int IsMatch(const void *data, const  void *param);

int main()
{
	pq_t *my_q = PQCreate(&IsBefore,NULL);
	
	student_t a = {"Hadas", 23435};
	student_t b = {"Gabriel", 33333};
	student_t c = {"Daniela", 12677};
	student_t *test =NULL;
	
	char* param = "Hadas";
	
	printf("testing Enqueue:\n");
	PQEnqueue(my_q, &a);
	PQEnqueue(my_q, &b);
	PQEnqueue(my_q, &c);
	if (PQCount(my_q) == 3)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}

	printf("\n testing peek\n");
	test = PQPeek(my_q);
	printf("the first in line : name = %s  id= %d \n", test->name,test->id);
	
	
	
	printf("\n testing Dequeue\n");
	printf("printing the values\n");
	test = PQDequeue(my_q);
	printf("the first out : name = %s  id= %d \n", test->name,test->id);

	test = PQDequeue(my_q);
	printf("the second out : name = %s  id= %d \n", test->name,test->id);

	test = PQDequeue(my_q);
	printf("the third out : name = %s  id= %d \n", test->name,test->id);
	
	printf("\ntesting count\n");
	if(PQCount(my_q) == 0)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	PQEnqueue(my_q, &c);
	if(PQCount(my_q) == 1)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	printf("\ntesting IsEmpty\n");
	if(PQIsEmpty(my_q) == 0)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	PQDequeue(my_q);
	if(PQIsEmpty(my_q) == 1)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	printf("\ntesting Erase\n");
	PQEnqueue(my_q, &a);
	PQEnqueue(my_q, &b);
	PQEnqueue(my_q, &c);
	
	PQErase(my_q, &IsMatch, param);
	while (!PQIsEmpty(my_q))
	{
		test = PQDequeue(my_q);
		printf("the data taken out : name = %s  id= %d \n", test->name,test->id);
	}	

	PQDestroy(my_q);
	
	return 0;
}


int IsBefore(const void *newdata, const void* cmpdata, void *param)
{
	(void)param;
	return   ((((student_t *)newdata)->id - ((student_t *)cmpdata)->id) < 0);
}

int IsMatch(const void *data, const void *param)
{
	return   (((student_t *)data)->name == (char *)param);
}


