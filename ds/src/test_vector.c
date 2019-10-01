#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "vector.h"

typedef struct 
{
	int id;
	float age;
} person_t;

int main()
{
	vector_t *test_vector = NULL;
	person_t person1 = {30, 18.5};
	person_t *person_tmp = NULL;
	size_t size_of_vector = 10;
	size_t temp_size = 0;
	size_t i = 0;
	int is_succsess = 0;

	/*######################## test VectorCreate #############################*/
	test_vector = VectorCreate( sizeof(person_t), size_of_vector);
	

	/*###################### test VectorGetItemAddress #######################*/
	for (i = 0; size_of_vector > i; i++)
	{
		person_tmp = (person_t*)VectorGetItemAddress(test_vector, i);
		person_tmp->id = person1.id + i;
		person_tmp->age = person1.age + i * 0.5;
	}

	printf("***Create & GetItemAddress***\n");
	for (i = 0; size_of_vector > i; i++)
	{
		person_tmp = (person_t*)VectorGetItemAddress(test_vector, i);
		printf("i = %lu \tid = %d \tage = %.2f\n", i, person_tmp->id, person_tmp->age);
	}


	/*###################### test VectorGetItemAddress #######################*/	
	printf("\n***SIZE***\nsize = %lu\n", VectorSize(test_vector));


	/*######################### test VectorCapacity ##########################*/	
	printf("\n***CAPACITY***\ncapacity = %lu\n", VectorCapacity(test_vector));

	/*######################## test VectorPopBack #1 #########################*/	
	VectorPopBack(test_vector);
	person_tmp = (person_t*)VectorGetItemAddress(test_vector,  VectorSize(test_vector) - 1);
	printf("\n***POP***\nid = %d \tage = %.2f\n", person_tmp->id, person_tmp->age);
	printf("\nPOP #1 capacity = %lu\n", VectorCapacity(test_vector));
	printf("POP #1 size = %lu\n", VectorSize(test_vector));


	/*######################### test VectorPushBack ##########################*/
	VectorPushBack(test_vector, &person1);
	person_tmp = (person_t*)VectorGetItemAddress(test_vector,  VectorSize(test_vector) - 1);
	printf("\n***PUSH***\nid = %d \tage = %.2f\n", person_tmp->id, person_tmp->age);
	printf("PUSH #1 capacity = %lu\n", VectorCapacity(test_vector));
	printf("PUSH #1 size = %lu\n", VectorSize(test_vector));


	VectorPushBack(test_vector, &person1);
	person_tmp = (person_t*)VectorGetItemAddress(test_vector, VectorSize(test_vector) - 1);
	printf("\nid = %d \tage = %.2f\n", person_tmp->id, person_tmp->age);
	printf("PUSH #2 capacity = %lu\n", VectorCapacity(test_vector));
	printf("PUSH #2 size = %lu\n", VectorSize(test_vector));


	VectorPushBack(test_vector, &person1);
	person_tmp = (person_t*)VectorGetItemAddress(test_vector, VectorSize(test_vector) - 1);
	printf("\nid = %d \tage = %.2f\n", person_tmp->id, person_tmp->age);
	printf("PUSH #3 capacity = %lu\n", VectorCapacity(test_vector));
	printf("PUSH #3 size = %lu\n", VectorSize(test_vector));


	/*######################## test VectorPopBack resize #########################*/	
	VectorPopBack(test_vector);
	VectorPopBack(test_vector);
	VectorPopBack(test_vector);
	VectorPopBack(test_vector);
	printf("\n***POP-RESIZE***\nPOP-before-resize capacity = %lu\n", VectorCapacity(test_vector));
	printf("POP-before-resize size = %lu\n", VectorSize(test_vector));
	VectorPopBack(test_vector);
	printf("\nPOP-after-resize capacity = %lu\n", VectorCapacity(test_vector));
	printf("POP-after-resize  = %lu\n", VectorSize(test_vector));

	/*######################### test VectorReserve ###########################*/
	temp_size = VectorSize(test_vector);
	is_succsess = VectorReserve(test_vector,200);
	printf("\n***RESERVE***\nnew RESERVE capacity = %lu\n", VectorCapacity(test_vector));
	printf("is succsess = %d\n", is_succsess);
	printf("is size unchanged = %d\n", VectorSize(test_vector) == temp_size);


	/*######################### test the Final Array ###########################*/
	printf("\n***FINAL ARRAY***\n");
	for (i = 0; VectorSize(test_vector) > i; i++)
	{
		person_tmp = (person_t*)VectorGetItemAddress(test_vector, i);
		printf("i = %lu \tid = %d \tage = %.2f\n", i, person_tmp->id, person_tmp->age);
	}
	printf("FINAL capacity = %lu\n", VectorCapacity(test_vector));
	printf("FINAL size = %lu\n", VectorSize(test_vector));

	/*######################### test VectorDestroy ###########################*/	
	VectorDestroy(test_vector);

	return 0;
}




