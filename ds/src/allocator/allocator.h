#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stddef> /* size_t */


typedef struct allocator alloc_t;

/* Initializes  */
alloc_t *ALInit(void *buffer, size_t buffer_size, size_t block_size);

void ALDestroy(alloc_t *buffer);

void *ALAlloc(alloc_t *buffer, void *block);

size_t ALCountFreeBlocks(const alloc_t *buffer);

size_t ALSuggest(size_t num_of_blocks, size_t size_of_block);

#endif /* __ALLOCATOR_H__ */
