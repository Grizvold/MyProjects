#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc */

#include "Mem.h" 

static const size_t word_size = sizeof(size_t);

/* fill buffer of word_size by c */
static size_t *FillWordBuffer(int c)
{
	size_t i = 0;
	char *buffer = NULL;
	
	/* create buffer in size_of_word */
	buffer = (char *)calloc(sizeof(char), word_size); 

	/* check for successful buffer initialization */
	if(NULL == buffer)
	{
		return NULL;
	}

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
	char *iterator = NULL;
	size_t *filled_buffer = NULL;

	/* point to first address of source block */
	iterator = (char *)source;
	
	/* fill "head" of our block bit-by-bit (case of unaligned addresses)	*/
	/* untill we reach aligned address								*/ 
	for(;
		0 != ((size_t)iterator % word_size) && 0 < n; 
		iterator++, n--)
	{
		*iterator = c;
	}
	
	/* fill buffer of word_size with int c */
	filled_buffer = FillWordBuffer(c);

	/* fill the aligned address with word size elements */
	for(; n > word_size; n -= word_size, iterator += word_size)
	{
		*((size_t *)iterator) = *filled_buffer;
	}

	/* fill the "tail" bit-by-bit */
	for(; 0 < n; n--, iterator++)
	{	
		*iterator = c;
	}

	free(filled_buffer);
	filled_buffer = NULL;

	return source;
}


void *MemCpy(void *dest, const void *src, size_t n)
{	
	char *dest_iterator = NULL;
	char *source_copy = NULL;
	
	dest_iterator = (char *)dest;
	source_copy = (char *)src;	

	/* copy src to dest byte-by-byte untill aligned address reached */
	for(; 0 != ((size_t)dest_iterator % word_size) && 0 < n; n--)
	{
		*dest_iterator++ = *source_copy++;
	}
	
	/* copy word-by-word */
	for(;
		n > word_size;
		n -= word_size, dest_iterator += word_size , source_copy += word_size)
	{
		*((size_t *)dest_iterator) = *((size_t *)source_copy);
	}
	
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


	/* if src overlaps with beginning of dest, copy from end to start */
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

