#include <stdio.h> 	/* printf */
#include <stddef.h> /* size_t	*/

#include "fsa.h"

int main()
{
	size_t iter = 0;
	size_t num_of_blocks = 0;
	size_t size_of_block = 0;
	size_t buffer_size = 50;
	char buffer[100] = {0};	
	fsa_t *fsa_test = NULL;
	
	
/***************************** Testing FSASuggest *****************************/	
	printf("\t Testing FSASuggest \n");
	size_of_block = 7;
	for(iter = 0; iter < 3; ++iter)
	{
		num_of_blocks = iter;
		printf("block num %lu, block size %lu, result %lu\n",
				num_of_blocks,
				size_of_block,
				FSASuggest(num_of_blocks, size_of_block));
	}
	
	size_of_block = 17;
	for(iter = 0; iter < 4; ++iter)
	{
		num_of_blocks = iter;
		printf("block num %lu, block size %lu, result %lu\n",
				num_of_blocks,
				size_of_block,
				FSASuggest(num_of_blocks, size_of_block));
	}
	
	size_of_block = 8;
	for(iter = 0; iter < 5; ++iter)
	{
		num_of_blocks = iter;
		printf("block num %lu, block size %lu, result %lu\n",
				num_of_blocks,
				size_of_block,
				FSASuggest(num_of_blocks, size_of_block));
	}
/******************************************************************************/	

/****************************** Testing FSAInit *******************************/
	size_of_block = 12;
	fsa_test = FSAInit(&buffer, buffer_size, size_of_block);
/******************************************************************************/
	return 0;
}
