#include <stdio.h>
#include <stdlib.h>

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)


int SuggestTest();
int InitTest1();
int InitTest2();
int CountTest();
int FreeTest();


int main()
{
	SuggestTest();

	InitTest1();

	InitTest2();

	CountTest();

	FreeTest();

	return 0;
}

/********************************************************/

int SuggestTest()
{
	size_t num_of_blocks = 3;
	size_t block_size = 3;
	size_t expected = 56;
	size_t result = 0;

	puts("\n************************************");
	puts("\nSuggest Test");

	result =  FSASuggest(num_of_blocks, block_size);
	
	if(result != expected)
	{
		puts("Error in Suggest test 1");
	}

	num_of_blocks = 2;
	block_size = 8;
	expected = 40;
	result =  FSASuggest(num_of_blocks, block_size);
	
	if(result != expected)
	{
		puts("Error in Suggest test 2");
	}

	num_of_blocks = 1;
	block_size = 1;
	expected = 24;
	result =  FSASuggest(num_of_blocks, block_size);
	
	if(result != expected)
	{
		puts("Error in Suggest test 3");
	}

	return 0;
}

/********************************************************/

int InitTest1()
{
	size_t num_of_blocks = 3;
	size_t block_size = 2;
	size_t actual_block = 0;
	ptrdiff_t result = 0;
	void *alloc = NULL;
	fsa_t *fsa = NULL;
	ptrdiff_t answer[] = {8, 24, 40, -1};
	int i = 0;

	puts("\n************************************");
	puts("\nInit Test1");

	result =  FSASuggest(num_of_blocks, block_size);

	actual_block = block_size + WORD_SIZE;

	while (actual_block % WORD_SIZE != 0)
	{
		++actual_block;
	} 

	alloc = malloc(62);

	fsa = FSAInit(alloc, result, block_size);

	result = *(size_t *)fsa;

	if (result != answer[i])
	{
		puts("Error in Init 1");
	}

	++i;

	alloc = (char *)alloc + WORD_SIZE;	

	while ((result % 8 == 0) && (result != -1))
	{
		result = *(size_t *)alloc;
	
		if (result != answer[i])
		{
			puts("Error in Init 2");
			printf("%ld", result);
		}

		++i;
		alloc = (char *)alloc + actual_block; 
	}		

	free(fsa);

	return 0;
}

/********************************************************/

int InitTest2()
{
	size_t num_of_blocks = 5;
	size_t block_size = 8;
	size_t actual_block = 0;
	ptrdiff_t result = 0;
	void *alloc = NULL;
	fsa_t *fsa = NULL;
	ptrdiff_t answer[] = {8, 24, 40, 56, 72, -1};
	int i = 0;

	puts("\n************************************");
	puts("\nInit Test 2");

	result =  FSASuggest(num_of_blocks, block_size);

	actual_block = block_size + WORD_SIZE;

	while (actual_block % WORD_SIZE != 0)
	{
		++actual_block;
	} 

	alloc = malloc(result);

	fsa = FSAInit(alloc, result, block_size);

	result = *(size_t *)fsa;

	if (result != answer[i])
	{
		puts("Error in Init 1");
	}

	++i;

	alloc = (char *)alloc + WORD_SIZE;	

	while ((result % 8 == 0) && (result != -1))
	{
		result = *(size_t *)alloc;
	
		if (result != answer[i])
		{
			puts("Error in Init 2");
		}

		++i;
		alloc = (char *)alloc + actual_block; 
	}		

	free(fsa);

	return 0;
}

/********************************************************/

int CountTest()
{	
	size_t num_of_blocks = 8;
	size_t block_size = 3;
	size_t result = 0;
	void *alloc = NULL;
	fsa_t *fsa = NULL;
	size_t answer[] = {7, 6, 5, 4, 3, 2, 1, 0};
	int i = 0;
	void *alloc_return = NULL;

	puts("\n************************************");
	puts("\nCount Test");

	result =  FSASuggest(num_of_blocks, block_size);

	alloc = malloc(result);

	fsa = FSAInit(alloc, result, block_size);

	alloc_return = FSAAlloc(fsa);

	while (alloc_return != NULL)
	{
		result = FSACountFreeBlocks(fsa);

		if (result != answer[i])
		{
			puts("Error in Count 1");
		}

		alloc_return = FSAAlloc(fsa);
		++i;		
	}

	free(alloc);

	return 0;
}

/********************************************************/

int FreeTest()
{
	size_t num_of_blocks = 7;
	size_t block_size = 3;
	size_t result = 0;
	void *alloc = NULL;
	fsa_t *fsa = NULL;
	size_t answer2[] = {0, 1, 2, 3, 4, 5, 6};
	int i = 0;
	void *pointers[8];

	puts("\n************************************");
	puts("\nFree Test");

	result =  FSASuggest(num_of_blocks, block_size);

	alloc = malloc(result);

	fsa = FSAInit(alloc, result, block_size);

	for (i = 0; i < 7; i++)
	{
		pointers[i] = FSAAlloc(fsa);
	}


	for (i = 0; i < 6; i++)
	{
		result = FSACountFreeBlocks(fsa);

		if (result != answer2[i])
		{
			puts("Error in Free");
		}

		FSAFree(pointers[i]);
	}

	free(alloc);

	return 0;
}	















