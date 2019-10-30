#include <stddef.h> /* size_t/ ptrdiff_t */
#include <assert.h> /* 		assert	 */
#include <stdlib.h> /*   	free		 */

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
	fsa_t *management_struct = NULL;
	size_t element_size = 0;
	size_t num_of_elements = 0;
	size_t offset = 0;
	
	assert(NULL != buffer);
	
	management_struct = buffer;
	management_struct->next_free = sizeof(*management_struct);
	
	/* aligned data block + word_size ("header" - next block)	*/
	element_size = AligningFunc(block_size) + WORD_SIZE;
	num_of_elements = (buffer_size - sizeof(*management_struct)) / element_size;
	
	offset = sizeof(*management_struct);
	
	/* Move pointer past management struct.					*/
	buffer = (char *)buffer + offset;
	
	/* Divide buffer to elements
	   Init elements so each element has 
		an offset of the next free element.				*/
	for(; num_of_elements > 1; --num_of_elements)
	{
		/* put offset of next free element
			into curret element "header" 					*/
		offset += element_size; 
		*(ptrdiff_t *)buffer = offset;
		/* move to next element */
		buffer = (char *)buffer + element_size;	
	}
	
	/* indicator that signs end of allocated buffer 			*/
	*(ptrdiff_t *)buffer = -1;
	
	return management_struct;
}

/*  Allocates next free block for user
    In case there is no free blocks, return NULL				*/
void *FSAAlloc(fsa_t *fsa)
{
	void *free_element_ptr = NULL;
	ptrdiff_t offset_to_next_free = 0;
	
	assert(NULL != fsa);
	
	/* no free elements left */
	if(-1 == fsa->next_free)
	{
		
		return NULL;
	}
	
	/* move to free element in buffer						*/
	free_element_ptr = (char *)fsa + fsa->next_free;
	offset_to_next_free = *(ptrdiff_t *)free_element_ptr;
	
	/* get offset to next free element						*/
	*(ptrdiff_t *)free_element_ptr = (ptrdiff_t)free_element_ptr - (ptrdiff_t)fsa;
	fsa->next_free = offset_to_next_free;
	
	free_element_ptr = (char *)free_element_ptr + WORD_SIZE;
	
	return free_element_ptr;
}

void FSAFree(void *block)
{
	size_t offset = 0;
	void *manage = NULL;
	fsa_t *location = NULL;

	assert(NULL != block);	

	block = (char *)block - WORD_SIZE;
	offset = *(size_t *)block;
	manage = (char *)block - offset;
	
	location = manage;	

	/* swap data in management struct and in block */
	*(size_t *)block = location->next_free;
	location->next_free = offset;	
}

size_t FSACountFreeBlocks(const fsa_t *fsa)
{
	const void *element_itr = NULL;
	ptrdiff_t next_free_element = 0;
	size_t free_blocks = 0;
	
	assert(NULL != fsa);

	next_free_element = fsa->next_free;
	element_itr = fsa;
	
	
	for(; -1 != next_free_element; next_free_element = *(ptrdiff_t *)element_itr)
	{
		element_itr = (char *)fsa + *(ptrdiff_t *)element_itr;
		free_blocks++;
	}
	
	return free_blocks;
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
/******************************************************************************/
static size_t AligningFunc(size_t num_test)
{
	return ((num_test + WORD_SIZE - 1) & ~(WORD_SIZE - 1));
}
