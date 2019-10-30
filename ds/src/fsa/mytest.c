#include <stdio.h> 	/* 	printf 		*/
#include <stddef.h> /* size_t/ptrdiff_t	*/
#include <stdlib.h> /* 	free/malloc 	*/

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

/***************************** Testing Functions  *****************************/
void FSASuggestTest();
void FSAInitTest();
/******************************************************************************/

/***************************** Assistant Functions  ***************************/
/******************************************************************************/

/***************************** Testing Components *****************************/
static size_t iter = 0;
static size_t num_of_blocks = 0;
static size_t size_of_block = 0;
static size_t buffer_size = 80;
static fsa_t *fsa_test = NULL;
/******************************************************************************/

int main()
{
	FSASuggestTest();
	FSAInitTest();
	return 0;
}	
/***************************** Testing FSASuggest *****************************/
void FSASuggestTest()
{	
	printf("\t Testing FSASuggest \n");
	size_of_block = 7;

	printf("\n1st test\n");
	for(iter = 0; iter < 3; ++iter)
	{
		num_of_blocks = iter;
		printf("block num %lu, block size %lu, result %lu\n",
				num_of_blocks,
				size_of_block,
				FSASuggest(num_of_blocks, size_of_block));
	}
	
	printf("\n2nd test\n");
	size_of_block = 12;
	for(iter = 0; iter < 4; ++iter)
	{
		num_of_blocks = iter;
		printf("block num %lu, block size %lu, result %lu\n",
				num_of_blocks,
				size_of_block,
				FSASuggest(num_of_blocks, size_of_block));
	}
	
	printf("\n3d test\n");
	size_of_block = 8;
	for(iter = 0; iter < 5; ++iter)
	{
		num_of_blocks = iter;
		printf("block num %lu, block size %lu, result %lu\n",
				num_of_blocks,
				size_of_block,
				FSASuggest(num_of_blocks, size_of_block));
	}
}
/******************************************************************************/	

/****************************** Testing FSAInit *******************************/
void FSAInitTest()
{
	static void  *buffer = NULL;	
	static init_test_results1[] =  {8, 32, 54, 80};
	size_t test_iter = 0;
	size_t size_of_element = 0;
	
	printf("\n\t Testing FSAInit \n");
	
	printf("\n1st test\n");
	num_of_blocks = 3;
	size_of_block = 12;
	size_of_element = 24;
	buffer = malloc(100);
	
	buffer_size = FSASuggest(num_of_blocks, size_of_block);
	fsa_test = FSAInit(buffer, buffer_size, size_of_block);
	
	if (init_test_results1[test_iter] != *(ptrdiff_t *)fsa_test)
	{
		printf("failure struct management in 1st test\n");
	}
	
	buffer = (ptrdiff_t *)buffer + WORD_SIZE;
	test_iter++;
	
	for(;
		-1 != *(ptrdiff_t *)buffer;
		buffer = (ptrdiff_t *)buffer + size_of_element)
	{
		if (*(ptrdiff_t *)buffer != init_test_results1[test_iter])
		{
			printf("failure in block num %lu\n", test_iter);
		}
		
		test_iter++;
	}
	
	free(buffer);
}
/******************************************************************************/
