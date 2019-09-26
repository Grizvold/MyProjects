#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

vector_t *VectorCreate(size_t element_size, size_t num_of_elements);

void VectorDestroy(vector_t *element);

/*	returns address of requested element in dynamic
	array in position represented by index value		 */
void *VectorGetItemAddress(vector_t *element, size_t index);

/* 	add element to the end of the dynamic array, if
	we reached array capacity, allocate capacity * 2 
	to expand the array							 
	return -1 for failure
		   0 for success						*/
int VectorPushBack(vector_t *element,const void *data);

/*	removes last element of dynamic array
	if empty 0, if success 1, if failure -1			*/
int VectorPopBack(vector_t *element);

/*   return how much elements currently are in
	dynamic array								*/
size_t VectorSize(const vector_t *element);

/* 	return capacity of our dynamic array, stored
	members + empty space left					*/
size_t VectorCapacity(const vector_t *element);

/* 	in case size reached capacity, allocate 
	capacity * 2 to dynamic array for new elements
	to come (dynamic vector)						*/
int VectorReserve(vector_t *element, size_t new_capacity);

#endif /* __VECTOR_H__ */
