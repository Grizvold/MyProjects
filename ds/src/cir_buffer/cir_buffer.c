#include <stdio.h> 	/* 		perror 	*/
#include <stddef.h> /* size_t/offsetof	*/
#include <assert.h> /* 		assert	*/
#include <stdlib.h> /* 	   malloc/free */

#include "cir_buffer.h"

struct cir_buffer
{
	size_t capacity;
	size_t tail_index;
	size_t head_index;
	int is_full;
	char data[1]; /* flexible array */
};

cir_buffer_t *CBCreate(size_t capacity)
{
	cir_buffer_t *new_cir_buffer = NULL;
	
	new_cir_buffer = (cir_buffer_t *)malloc(offsetof(cir_buffer_t, data) + capacity);
	if(NULL == new_cir_buffer)
	{
		perror("malloc in CBCreate failed");
	
		return NULL;
	}
	
	new_cir_buffer->tail_index = 0;
	new_cir_buffer->head_index = 0;
	new_cir_buffer->capacity = capacity;
	new_cir_buffer->is_full = 0;
	
	return new_cir_buffer;
}

void CBDestroy(cir_buffer_t *circ_buffer)
{
	assert(NULL != circ_buffer);

	free(circ_buffer);
}

size_t CBWrite(cir_buffer_t *circ_buffer, void *data, size_t num_bytes)
{
	size_t bytes_written = 0;
	
	assert(NULL != circ_buffer && circ_buffer->data);
	
	for(bytes_written = 0; 0 != num_bytes; num_bytes--, bytes_written++)
	{
		circ_buffer->data[circ_buffer->head_index] = ((char *)data)[bytes_written];
		
		if(1 == circ_buffer->is_full)
		{
			circ_buffer->tail_index = 
					(circ_buffer->tail_index + 1) % circ_buffer->capacity;
		}
		
		circ_buffer->head_index = (circ_buffer->head_index + 1) % circ_buffer->capacity;
		circ_buffer->is_full = (circ_buffer->head_index == circ_buffer->tail_index);
	}
	
	return bytes_written;
}

size_t CBRead(cir_buffer_t *circ_buffer, void *buffer, size_t num_bytes)
{
	size_t bytes_read = 0;

	assert(NULL != circ_buffer && NULL != buffer && circ_buffer->data);
	
	for(bytes_read = 0; 0 != num_bytes && !(CBIsEmpty(circ_buffer)); num_bytes--, bytes_read++)
	{
		((char *)buffer)[bytes_read] = circ_buffer->data[circ_buffer->tail_index];
		circ_buffer->tail_index = (circ_buffer->tail_index + 1) % circ_buffer->capacity;
	}
	
	circ_buffer->is_full = 0;
	
	return bytes_read;
}

int CBIsEmpty(const cir_buffer_t *circ_buffer)
{
	return (!(circ_buffer->is_full) && (circ_buffer->head_index == circ_buffer->tail_index));
}

size_t CBCapacity(const cir_buffer_t *circ_buffer)
{
	assert(NULL != circ_buffer);
	
	return circ_buffer->capacity;
}

size_t CBGetFreeSpace(const cir_buffer_t *circ_buffer)
{
	size_t free_space = 0;
	
	if(0 == circ_buffer->is_full)
	{
		if(circ_buffer->head_index >= circ_buffer->tail_index)
		{
			free_space = circ_buffer->capacity - 
					circ_buffer->head_index + circ_buffer->tail_index;
		}
	
		if(circ_buffer->head_index < circ_buffer->tail_index)
		{
			free_space = circ_buffer->tail_index - circ_buffer->head_index;
		}
	}
	
	return free_space;
}
