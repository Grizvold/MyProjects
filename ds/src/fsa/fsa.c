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

/***************************** FSA Functionality  *****************************/

/*  	*"Header" of each element will have offset to the next element
		(which is free element).									   */
fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size)
{
	fsa_t *management_struct = NULL;
	size_t offset = 0;
	size_t element_size = 0;
	size_t num_of_elements = 0;
	
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

/*  *Allocates next free block for user.
    *In case there is no free blocks, return NULL.					   */
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
	
	/* set "header" of cur element to offset from management 
	   struct and set management struct to the next
	   free element offset								*/
	*(ptrdiff_t *)free_element_ptr = (ptrdiff_t)free_element_ptr - (ptrdiff_t)fsa;
	fsa->next_free = offset_to_next_free;
	
	/* move pointer past "header", which indicates the offset 
	   of next free element								*/
	free_element_ptr = (char *)free_element_ptr + WORD_SIZE;
	
	return free_element_ptr;
}

/* 	*Get offset of current block compared to management struct,
		and mark the current element as free, by putting its 
		offset into management struct.							   */
void FSAFree(void *block)
{
	fsa_t *management_struct = NULL;
	void *ptr_management_struct = NULL;
	ptrdiff_t offset_to_free_element = 0;

	assert(NULL != block);	

	/* move to "header" of curret element to get offset
	   for struct management								*/
	block = (char *)block - WORD_SIZE;
	offset_to_free_element = *(ptrdiff_t *)block;

	ptr_management_struct = (char *)block - offset_to_free_element;
	management_struct = ptr_management_struct;	

	/* get offset for next free element from management struct
	   and put it inside "head" of current element			*/
	*(ptrdiff_t *)block = management_struct->next_free;
	management_struct->next_free = offset_to_free_element;	
}

size_t FSACountFreeBlocks(const fsa_t *fsa)
{
	size_t free_blocks = 0;
	const void *element_itr = NULL;
	ptrdiff_t offset_to_next_free = 0;
	
	assert(NULL != fsa);

	offset_to_next_free = fsa->next_free;
	element_itr = fsa;
	
	
	for(; -1 != offset_to_next_free; offset_to_next_free = *(ptrdiff_t *)element_itr)
	{
		element_itr = (char *)fsa + *(ptrdiff_t *)element_itr;
		free_blocks++;
	}
	
	return free_blocks;
}

/*  *Aligns requested block size, and returns suggested size of buffer	   */
size_t FSASuggest(size_t num_of_blocks, size_t size_of_block)
{
	size_t management_struct_size = 0;
	
	management_struct_size = sizeof(fsa_t);
	
	return (management_struct_size + 
			AligningFunc(WORD_SIZE + size_of_block) * num_of_blocks);
}
/******************************************************************************/

/************* formula for calculating how much space to allocate *************/
/* 	size_t num = 12; 											   */
/* 	size_t mod = 8;											   */
/* 	size_t result = 0; 											   */
/* 	result = (num + mod - 1) & ~(mod - 1);							   */
/******************************************************************************/
static size_t AligningFunc(size_t num_test)
{
	return ((num_test + WORD_SIZE - 1) & ~(WORD_SIZE - 1));
}
