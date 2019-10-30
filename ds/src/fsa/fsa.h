#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stddef.h> /* size_t */

/***************************** FSA typedefs ***********************************/
typedef struct fsa fsa_t;
/******************************************************************************/

/***************************** FSA Functionality  *****************************/
/* *Initializes fixed size allocator by following steps:
	Putting at the beginning of the buffer management struct that has 
		an offset to the next free element.
	Divide rest of buffer to elements, where each element has "header" 
		that indicates offset to the next free element(currently next).
	Sign the end of an aligned buffer by putting in "header" of the 
		last element "-1".	
   *Return fixed size allocator.									   */
fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size);

/* *Allocate free block by following steps:
	Go to the first free element. (That management struct has offset to).
	Put his "header" value that is an offset to next free block into 
		management struct.
	Change his "header" value to an offset compared to management struct.
   *Return pointer to free block.
   *Complexity O(1).											   */
void *FSAAlloc(fsa_t *fsa);

/* *Mark requested block as free, by putting its offset into management
	struct, and its own "header" will have offset to the next free element.
   *Complexity O(1).											   */
void FSAFree(void *block);

/* *Returns number of free blocks in requested buffer.					   */
size_t FSACountFreeBlocks(const fsa_t *fsa);

/* *Aligns requested block size to current working architecture.
   *Returns suggested size for the whole buffer that includes 
   	management struct + "header" for each block that has
   	offset to the next free element.								   */
size_t FSASuggest(size_t num_of_blocks, size_t size_of_block);
/******************************************************************************/

#endif /* __ALLOCATOR_H__ */
