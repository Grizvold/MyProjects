#include <stdlib.h> /* malloc, calloc, free */
#include <stdio.h> /* perror */

#include "vector.h"

struct vector
{
	size_t element_size;
	size_t capacity;
	size_t size;
	void *base;
};

vector_t *VectorCreate(size_t element_size, size_t num_of_elements)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	if(NULL == vector)
	{
		perror("Malloc failed: ");
		return NULL;
	}
	
	vector->base = calloc(element_size, num_of_elements);
	if(NULL == vector)
	{
		perror("Calloc failed: ");
		return NULL;
	}
	
	vector->element_size = element_size;
	vector->capacity = num_of_elements;
	vector->size = num_of_elements;
	
	return vector;
}

int VectorPushBack(vector_t *vector, const void *data)
{
	if(vector->size == vector->capacity)
	{
		void *new_vector = realloc(vector->base, 
							vector->capacity * vector->element_size * 2)
		if(NULL == new_vector)
		{
			return -1;
		}
		
		vector->base = new_vector;
		vector->capcity *= 2;
		vector->size += 1;
		memcpy		
	}
	else
	{
		size++
		copy	
	}	
	
	return 0;
}
int VectorPopBack(vector_t *vector)
{
	vector->base 	

	return 1;
}

void *VectorGetItemAddress(vector_t *vector, size_t index)
{
	return (char *)vector->base + (index * vector->element_size);
}

size_t VectorSize(const vector_t *vector)
{
	return vector->size;
}

size_t VectorCapacity(const vector_t *vector)
{
	return vector->capacity;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	
}

void VectorDestroy(vector_t *vector)
{
	free(vector->base);
	vector->base = NULL;
	
	free(vector);
	vector = NULL;	
}

