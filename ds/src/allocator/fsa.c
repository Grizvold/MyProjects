#include <stddef.h> /* size_t/ ptrdiff_t */
#include <assert.h> /* 	assert		 */
#include <stdio.h>

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

/*************************** Management struct ********************************/
struct fsa
{
	ptrdiff_t next_free;
};
/******************************************************************************/

/************************** Auxiliary Component *******************************/
static size_t AligningFunc(size_t num_test);
/******************************************************************************/

fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size)
{
	char *starting_point = NULL;
	size_t element_size = 0;
	size_t num_of_elements = 0;
	size_t itr = 0;
	
	assert(NULL != buffer);
	
	starting_point = (char *)buffer;
	
	/* aligned data + word_size */
	element_size = AligningFunc(block_size) + WORD_SIZE;
	num_of_elements = buffer_size / element_size;
	
	for(; buffer_size > element_size; buffer_size -= element_size)
	{
		*(ptrdiff_t *)(buffer) = (ptrdiff_t)((char *)buffer + element_size - starting_point);
				
	}
	
	printf("\nbuffer size %lu, number of blocks %lu, block size %lu \n", buffer_size, num_of_elements, element_size);
	
	
	
	return (fsa_t *)buffer;
}

size_t FSASuggest(size_t num_of_blocks, size_t size_of_block)
{
	
	return AligningFunc(num_of_blocks * size_of_block);
}

/************* formula for calculating how much space to allocate *************/
/* 	size_t num = 24; 											   */
/* 	size_t mod = 8;											   */
/* 	size_t result = 0; 											   */
/* 	result = (num + mod - 1) & ~(mod - 1);							   */
static size_t AligningFunc(size_t num_test)
{
	return ((num_test + WORD_SIZE - 1) & ~(WORD_SIZE - 1));
}
