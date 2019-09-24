#include "Mem.h" 
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc */

#include <stdio.h> /* printf */

static const size_t word_size = sizeof(size_t);

/* fill buffer of word_size by byte c */
static size_t *FillWordBuffer(int c)
{
	size_t i = 0;
	char *buffer = NULL;
	
	/* create buffer in size_of_word */
	buffer = (char *)calloc(sizeof(char), word_size); 

	/* check for successful buffer initialization */
	assert(NULL != buffer);

	/* fill our word with character c */
	for(i = 0; i < word_size; i++)
	{
		*(buffer + i) = c;
	}
	
	return (size_t *)buffer;
}

/* fills first n bytes of the memory area pointed to by source with byte c */ 
void *MemSet(void *source, int c, size_t n)
{
	char *char_iterator = NULL;
	size_t *word_iterator = NULL;
	size_t *filled_buffer = NULL;

	/* point to first address of source block */
	char_iterator = (char *)source;
	
	/* fill "head" of our block bit-by-bit (unaligned addresses) */
	/* untill we reach aligned address 			*/ 
	for(; 0 != ((size_t)char_iterator % word_size) && 0 < n; char_iterator++, n--)
	{
		*char_iterator = c;
	}

	filled_buffer = FillWordBuffer(c); 
	word_iterator = (size_t *)char_iterator;

	/* fill the aligned address with word size elements */
	for(;0 < (n / word_size); n -= word_size, word_iterator++)
	{
		*word_iterator = *filled_buffer;
	}

	char_iterator = (char *)word_iterator;
	/* fill the "tail" bit-by-bit */
	for(; 0 < n; n--, char_iterator++)
	{	
		*char_iterator = c;
	}
	

	free(filled_buffer);
	filled_buffer = NULL;

	return source;
}


void *MemCpy(void *dest, const void *src, size_t n)
{	
	char *dest_iterator = NULL;
	char *source_copy = NULL;
	size_t *word_iterator = NULL;
	
	dest_iterator = (char *)dest;
	source_copy = (char *)src;	

	/* copy src to dest byte-by-byte untill aligned address reached */
	for(; 0 != ((size_t)dest_iterator % word_size) && 0 < n; dest_iterator++, source_copy++, n--)
	{
		*dest_iterator = *source_copy;
	}
	
	word_iterator = (size_t *)(dest_iterator);
	/* copy word-by-word */
	for(;0 < (n / word_size); n -= word_size
						, dest_iterator++ 
						, source_copy += word_size)
	{
		*word_iterator = *((size_t *)source_copy);
	}
	
	dest_iterator = (char *)word_iterator;
	/* copy tail if left byte-by-byte */
	for(; 0 < n; n--, dest_iterator++, source_copy++)
	{	
		*dest_iterator = *source_copy;
	}
	
	return dest;
	
}

void *MemMove(void *dest, const void *src, size_t n)
{
	char *c_src = (char *)src + n - 1;
	char *c_dest = (char *)dest + n - 1;
	size_t i = 0;

	/* in case that dest overlaps src copy from tail to head	*/
	/* because otherwise it fills dest with 1 char			*/
	if(((char *)src + n > (char *)dest) && src < dest)
	{
		for(i = 0; i < n; i++)
		{
			*(c_dest) = *(c_src);
			c_dest--;
			c_src--;
		}
	}
	/* in case that there is no overlap					 */
	else
	{
		dest = MemCpy(dest, src, n);
	}
	
	return dest;
}

