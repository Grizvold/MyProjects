#include <string.h> /* 		memcpy 		*/
#include <stdio.h>  /* 		perror		*/
#include <stdlib.h> /*	malloc, calloc, free	*/

#include "vector.h"

enum g_status{SUCCESS, FAILURE};

struct vector
{
	size_t element_size;
	size_t capacity;
	size_t size;
	void *base;
};

vector_t *VectorCreate(size_t num_of_elements, size_t element_size)
{
	vector_t *vector = (vector_t *)malloc(sizeof(*vector));
	if (NULL == vector)
	{
		perror("Malloc in VectorCreate failed");
		return NULL;
	}
	
	vector->base = calloc(num_of_elements, element_size);
	if (NULL == vector->base)
	{
		perror("Calloc in VectorCreate failed");
		return NULL;
	}
	
	vector->element_size = element_size;
	vector->capacity = num_of_elements;
	vector->size = 0;
	
	return vector;
}

void *VectorGetItemAddress(vector_t *vector, size_t index)
{
	return (char *)vector->base + (index * vector->element_size);
}

int VectorPushBack(vector_t *vector, const void *data)
{
	int exponential_growth = 2;
	
	if (vector->size == vector->capacity)
	{
		void *new_vector = realloc(vector->base, 
			vector->capacity * vector->element_size * exponential_growth);
		if (NULL == new_vector)
		{
			perror("Realloc in VectorPushBack failed");
			return FAILURE;
		}
		
		vector->base = new_vector;
		vector->capacity *= exponential_growth;
	}
	
	memcpy((char *)vector->base + (vector->size * vector ->element_size),
			data, vector->element_size);	
	vector->size += 1;
	
	return SUCCESS;
}

int VectorPopBack(vector_t *vector)
{
	float exponential_decay = 0.75;
	int grow_factor = 2;
	
	if(vector->size == (vector->capacity / grow_factor))
	{
		void *new_vector = realloc(vector->base, 
				vector->element_size * vector->capacity * exponential_decay);
		if (NULL == new_vector)
		{
			perror("Realloc in VectorPopBack failed");
			
			return FAILURE;
		}
		
			vector->base = new_vector;
			vector->capacity *= exponential_decay;
	}
	
	vector->size -= 1; 	

	return SUCCESS;
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
	if (new_capacity > (vector->capacity - vector->size))
	{
		void *new_vector = realloc(vector->base, 
					new_capacity * vector->element_size);
		if (NULL == new_vector)
		{
			perror("Realloc in VectorReserve failed");
			
			return FAILURE;
		}
		
		vector->base = new_vector;
		vector->capacity = new_capacity;
	}
	
	return SUCCESS;
}

void VectorDestroy(vector_t *vector)
{
	free(vector->base);
	vector->base = NULL;
	
	free(vector);
	vector = NULL;	
}

