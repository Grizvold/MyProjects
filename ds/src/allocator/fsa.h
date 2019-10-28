#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stddef.h> /* size_t */

/***************************** FSA typedefs ***********************************/

typedef struct fsa fsa_t;
/******************************************************************************/

/***************************** FSA Functionality  *****************************/
/* *Initializes fixed size allocator	
   *	*/
fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size);

void FSAInitDestroy(fsa_t *fsa);

/* *Complexity O(1). */
void *FSAAlloc(fsa_t *fsa);

/* *Complexity O(1). */
void FSAFree(void *block);

size_t FSAInitCountFreeBlocks(const fsa_t *fsa);

/* *Returns */
size_t FSASuggest(size_t num_of_blocks, size_t size_of_block);
/******************************************************************************/

#endif /* __ALLOCATOR_H__ */
