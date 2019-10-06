#include <stdio.h> 	/* perror */
#include <stddef.h> /* size_t	*/
#include <assert.h> /* assert */

#include "cir_buffer.h"

struct cir_buffer
{
	size_t capacity;
	size_t tail_index;
	size_t head_index;
	int is_full;
	char *data[1]; /* flexible array */
};

cir_buffer_t *CBCreate(size_t capacity)
{
	cir_buffer_t *new_cir_buffer = NULL;
	
	new_cir_buffer = (cir_buffer_t *)malloc(offsetof(new_cir_buffer, data) + capacity);
	if(NULL = new_cir_buffer)
	{
		perror("malloc in CBCreate failed");
	
		return NULL;
	}
	
	new_cir_buffer->reading_index = 0;
	new_cir_buffer->writing_index = 0;
	new_cir_buffer->capacity = capacity;
	new_cir_buffer->is_full = 0;
	
	return new_cir_buffer;
}

void CDDestroy(cir_buffer_t *circ_buffer)
{
	assert(NULL != circ_buffer);

	free(circ_buffer);
	circ_buffer = NULL;
}

size_t CBWrite(cir_buffer_t *circ_buffer, void *data, size_t num_bytes)
{
	assert(NULL != circ_buffer);
	
	circ_buffer->data[circ_buffer->head_index] = data;
	
	if(1 == circ_buffer->is_full)
	{
		circ_buffer->tail_index = 
				(circ_buffer->tail_index + 1) % circ_buffer->capacity;
	}
	
	circ_buffer->head_index = (circ_buffer->head_index + 1) % circ_buffer->capacity;
	circ_buffer->is_full = (circ_buffer->head_index == circ_buffer->tail_index);
}

