#include <stddef.h> /* size_t                        */
#include <stdio.h>  /* printf                        */

#include "queue.h"

void PrintAndDeQ(queue_t *queue);

/* data struct for testing*/
typedef struct 
{
	int serial_num;
	float f_num;
} test_struct_t;


int main()
{
	queue_t *queue_1 = NULL;
	queue_t *queue_2 = NULL;

	test_struct_t test_struct1 = {1, 0.1};
	test_struct_t test_struct2 = {2, 0.2};
	test_struct_t test_struct3 = {3, 0.3};
	test_struct_t test_struct4 = {4, 0.4};
	test_struct_t test_struct5 = {5, 0.5};
	test_struct_t test_struct6 = {6, 0.6};

	queue_1 = QueueCreate();

	printf("count = %lu\n", QueueCount(queue_1));
	printf("is empty? = %d\n", QueueIsEmpty(queue_1));

	QueueEnqueue(queue_1, &test_struct1);
	QueueEnqueue(queue_1, &test_struct2);
	QueueEnqueue(queue_1, &test_struct3);
	QueueEnqueue(queue_1, &test_struct4);
	
	printf("count = %lu\n", QueueCount(queue_1));
	printf("is empty? = %d\n", QueueIsEmpty(queue_1));

	printf("\n**** Peak ****\nserial_num in front - %d\n", 
		   ((test_struct_t*)QueuePeek(queue_1))->serial_num);


/*################################# DeQueue ##################################*/
	printf("\n**** DeQueue ****\nremoved (= 1) - %d\t", 
		   ((test_struct_t*)QueueDequeue(queue_1))->serial_num);
	printf("in front (= 2) - %d\t", 
		   ((test_struct_t*)QueuePeek(queue_1))->serial_num);
	printf("count = %lu\n", QueueCount(queue_1));


/*########################### DeQueue-EnQueue Flow ###########################*/
	printf("\n**** DeQ-EnQ Flow ****\nDeq:\nremoved (= 2) - %d\t", 
		   ((test_struct_t*)QueueDequeue(queue_1))->serial_num);
	printf("in front (= 3) - %d\t", 
		   ((test_struct_t*)QueuePeek(queue_1))->serial_num);
	printf("count = %lu\n", QueueCount(queue_1));

	printf("Deq:\nremoved (= 3) - %d\t", 
		   ((test_struct_t*)QueueDequeue(queue_1))->serial_num);
		printf("in front (= 3) - %d\t", 
		   ((test_struct_t*)QueuePeek(queue_1))->serial_num);
	printf("count = %lu\n", QueueCount(queue_1));

	QueueEnqueue(queue_1, &test_struct5);
	QueueEnqueue(queue_1, &test_struct6);

	printf("2*Enq + Deq:\nremoved (= 4) - %d\t", 
		   ((test_struct_t*)QueueDequeue(queue_1))->serial_num);
		printf("in front (= 5) - %d\t", 
		   ((test_struct_t*)QueuePeek(queue_1))->serial_num);
	printf("count = %lu\n", QueueCount(queue_1));
	
	printf("Deq:\nremoved (= 5) - %d\t", 
		   ((test_struct_t*)QueueDequeue(queue_1))->serial_num);
		printf("in front (= 6) - %d\t", 
		   ((test_struct_t*)QueuePeek(queue_1))->serial_num);
	printf("count = %lu\n", QueueCount(queue_1));

	printf("Deq:\nremoved (= 6) - %d\t", 
		   ((test_struct_t*)QueueDequeue(queue_1))->serial_num);
	printf("count = %lu\n", QueueCount(queue_1));

	QueueEnqueue(queue_1, &test_struct1);
		printf("Enq:\nin front (= 1) - %d\t", 
		   ((test_struct_t*)QueuePeek(queue_1))->serial_num);
	printf("count = %lu\n", QueueCount(queue_1));


/*################################# Append ###################################*/

	QueueEnqueue(queue_1, &test_struct2);
	QueueEnqueue(queue_1, &test_struct3);

	queue_2 = QueueCreate();
	QueueEnqueue(queue_2, &test_struct4);
	QueueEnqueue(queue_2, &test_struct5);
	QueueEnqueue(queue_2, &test_struct6);

	queue_2 = QueueAppend(queue_2, queue_1);

	printf("\n**** Append ****\nqueue_2 front (= 4) - %d\n", 
		   ((test_struct_t*)QueuePeek(queue_2))->serial_num);
	printf("queue_1 count = %lu\tqueue_2 count = %lu\n",
		   QueueCount(queue_1), QueueCount(queue_2));

	PrintAndDeQ(queue_2);

/*################################# Destroy ##################################*/
	QueueEnqueue(queue_1, &test_struct2);
	QueueEnqueue(queue_1, &test_struct3);

	QueueDestroy(queue_1);
	queue_1 = NULL;

	QueueDestroy(queue_2);
	queue_1 = NULL;

	return 0;
}

void PrintAndDeQ(queue_t *queue)
{
	printf("PRINT & DeQ:\n");
	 
	for (; 1 < QueueCount(queue); )
	{
		printf("removed = %d\t", 
			   ((test_struct_t*)QueueDequeue(queue))->serial_num);
		printf("in front = %d\t", 
			   ((test_struct_t*)QueuePeek(queue))->serial_num);
		printf("count = %lu\n", QueueCount(queue));
	}

	printf("removed = %d\tin front = \t", 
		   ((test_struct_t*)QueueDequeue(queue))->serial_num);
	printf("count = %lu\n", QueueCount(queue));
}



