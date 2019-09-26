#ifndef __vector_h__
#define __vector_h__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

vector_t *VectorCreate(size_t element_size, size_t num_of_elements);

void VectorDestroy(vector_t *element);

/*	returns address of requested element in dynamic
	array in position represented by index value		 */
void *VectorGetItemAddress(vector_t *element, size_t index);

int VectorPushBack(vector_t *element,const void *element);

/*	removes last element of dynamic array
	if empty 0, if success 1, if failure -1			*/
int VectorPopBack(vector_t *element);

size_t VectorSize(const vector_t *element);

size_t VectorCapacity(const vector_t *element);

int VectorReserve(const vector_t *element, size_t new_capacity);

#endif /* vector */
