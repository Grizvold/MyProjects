#include <stddef.h> /*	size_t	*/
#include <assert.h> /*	assert	*/

#include "vsa.h" /* vsa API */


/* ########################### Allocator Structs #############################*/
/* struct of the variable size allocator - for symbolic purpuses alone */
struct vsa
{
	char data[1];
};

/* struct of the vsa blocks */
typedef struct vsa_block
{
    #ifndef NDEBUG
    size_t magic_num;
    #endif /* NDEBUG */
	size_t header;
	char data[1]; /* flexible array */
} vsa_block_t;


/* ##################### Static Functions Declarations ###################### */
static size_t VSAAlignBufferSize(size_t buff_size);
static size_t VSACalcBlockSize(size_t block_size);
static int VSAIsBlockFree(vsa_block_t *block);
static int VSAIsEnd(vsa_block_t *block);
static vsa_block_t *VSANextBlock(vsa_block_t *block);
static size_t VSAGetBlockSize(vsa_block_t *block);
static void VSAMergeBlocks(vsa_block_t *block);
static int VSAFindSpace(vsa_block_t *block, size_t block_size);
#ifndef NDEBUG
static int VSAIsMagic(void *block_data);
#endif /* NDEBUG */


/* ######################### Const Static Variables ######################### */
static const size_t WORD_SIZE = sizeof(size_t);

 /* size of the header without the data, in bytes */
static const size_t HEADER_SIZE = offsetof(vsa_block_t, data);

 /* offset of the header-field, in size_t (bytes / word) */
static const size_t HEADER_OFFSET = offsetof(vsa_block_t, header) / sizeof(size_t);

 /* offset of the data-field, in size_t (bytes / word) */
static const size_t DATA_OFFSET = offsetof(vsa_block_t, data) / sizeof(size_t);

#ifndef NDEBUG
static const size_t magic = 0xCAFED00D;
#endif /* NDEBUG */


/* ####################### API Functions Definitions ######################## */
vsa_t *VSAInit(void *buffer, size_t buff_size)
{
	vsa_t *new_vsa = NULL;

	assert(NULL != buffer);    

	new_vsa = (vsa_t*)buffer;

	buff_size = VSAAlignBufferSize(buff_size);
	
	/* set an intial header with the free space in all of the buffer */
	((vsa_block_t*)new_vsa)->header = buff_size - HEADER_SIZE /*- WORD_SIZE*/;

	/* set a header in the end of the buffer to mark the end */
	VSANextBlock((vsa_block_t*)new_vsa)->header = 1;

	#ifndef NDEBUG
	((vsa_block_t*)new_vsa)->magic_num = magic;
	VSANextBlock((vsa_block_t*)new_vsa)->magic_num = magic;
	#endif /* NDEBUG */

	return new_vsa;
}

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	vsa_block_t *block = NULL;
	size_t block_size = 0;

	assert (NULL != vsa);
	assert (0 != n_bytes);

	block_size = VSACalcBlockSize(n_bytes);

	for (block = (vsa_block_t*)vsa;
		 !VSAIsEnd(block);
		 block = VSANextBlock(block))
	{
		if (VSAIsBlockFree(block))
		{
			/* VSAFindSpace returns 0 on success (enough space), 
			   1 on failure (not enough space)					*/
			if (0 == VSAFindSpace(block, block_size))
			{
				break;
			}
		}
	}

	if (VSAIsEnd(block) || block->header < block_size)
	{
		return NULL;
	}

	/* setting up a header at the end of the block */
	if (!VSAIsEnd((vsa_block_t*)((char*)block + block_size)))
	{
		((size_t*)block + block_size / WORD_SIZE)[HEADER_OFFSET] = 
			((size_t*)block)[HEADER_OFFSET] - block_size;
	}
	#ifndef NDEBUG
	block->magic_num = magic;
	#endif /* NDEBUG */

	/* mark the block as allocated */
	((size_t*)block)[HEADER_OFFSET] = block_size + 1;

	return block->data;
}

void VSAFree(void *block_data)
{
	assert(NULL != block_data);

	#ifndef NDEBUG
	if (!VSAIsMagic(block_data))
	{
		return;
	}
	#endif /* NDEBUG */
	
	/* bitwise shifts to ignore the IsFree bit (lsb) */
	((size_t*)block_data)[-DATA_OFFSET + HEADER_OFFSET] >>= 1;
	((size_t*)block_data)[-DATA_OFFSET + HEADER_OFFSET] <<= 1;
}

size_t VSAMaxFreeBlock(const vsa_t *vsa)
{
	vsa_block_t *block = NULL;
	size_t max_block = 0;
	
	for (block = (vsa_block_t*)vsa; !VSAIsEnd(block); block = VSANextBlock(block))
	{
		if (VSAIsBlockFree(block))
		{
			for (; VSAIsBlockFree(VSANextBlock(block)) && !VSAIsEnd(VSANextBlock(block));)
			{
				VSAMergeBlocks(block);
			}
			max_block = (VSAGetBlockSize(block) > max_block) ? VSAGetBlockSize(block) : max_block;
		}
	}

	max_block = (max_block < HEADER_SIZE) ? 0 : max_block - HEADER_SIZE;
	
	return max_block;
}


/* ###################### Static Functions Definitions ###################### */
static size_t VSAAlignBufferSize(size_t buff_size)
{
	buff_size /= WORD_SIZE;
	buff_size *= WORD_SIZE;

	return buff_size;
}

static size_t VSACalcBlockSize(size_t block_size)
{
	block_size = (0 == block_size % WORD_SIZE) ? 
				 block_size / WORD_SIZE : block_size / WORD_SIZE + 1;
	block_size *= WORD_SIZE;
	block_size += HEADER_SIZE;

	return block_size;
}

static int VSAIsBlockFree(vsa_block_t *block)
{
	return ((0 == ((size_t*)block)[HEADER_OFFSET] % 2) ? 1 : 0);
}

static int VSAIsEnd(vsa_block_t *block)
{
	return ((1 == block->header) ? 1 : 0);
}

static vsa_block_t *VSANextBlock(vsa_block_t *block)
{
	size_t block_size = 0;

	block_size = VSAGetBlockSize(block);

	return (vsa_block_t*)((size_t*)block + block_size / WORD_SIZE);
}

static size_t VSAGetBlockSize(vsa_block_t *block)
{
	size_t block_size = 0;

	/* retrive block size, while removing the effect of the IsFree bit (lsb) */
	block_size = ((size_t*)block)[HEADER_OFFSET];
	block_size >>= 1;
	block_size <<= 1;

	return block_size;
}

/* returns 0 on success (enough space), 1 on failure (not enough space) */
static int VSAFindSpace(vsa_block_t *block, size_t block_size)
{
	int is_enough_space = 0;
	
	for (; block_size > VSAGetBlockSize(block) /*+ HEADER_SIZE*/ &&
		 HEADER_SIZE != VSAGetBlockSize(block);)
	{
		if (VSAIsBlockFree(VSANextBlock(block)))
		{
			VSAMergeBlocks(block);
		}
		else
		{
			is_enough_space = 1;
			break;
		}
	}
	
	return is_enough_space;
}

static void VSAMergeBlocks(vsa_block_t *block)
{
	size_t next_block_offset = 0;

	next_block_offset = ((size_t*)block)[HEADER_OFFSET] / WORD_SIZE;
	((size_t*)block)[HEADER_OFFSET] += 
		((size_t*)block + next_block_offset)[HEADER_OFFSET];
}

#ifndef NDEBUG
static int VSAIsMagic(void *block_data)
{
	return (magic == *((size_t*)block_data - DATA_OFFSET));
}
#endif /* NDEBUG */






