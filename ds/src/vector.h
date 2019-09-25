#ifndef __vector_h__
#define __vector_h__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

VectorCreate(size_t element_size, size_t num_of_elements);

VectorDestroy(vector_t *element);

void *VectorGetItemAddress(vector_t *element, size_t index);

void VectorPushBack(vector_t *element, void *element);

void VectorPopBack(vector_t *element);

size_t VectorSize(const vector_t *element);

size_t VectorCapacity(const vector_t *element);

size_t VectorReserve(vector_t *element, size_t num_elements);

#endif /* vector */
