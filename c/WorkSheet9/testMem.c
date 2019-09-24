#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */
#include <string.h> /* strlen */

#include "Mem.h" /* memcpy/memset/memmove */

void testMemSet();
void testMemCpy();
void testMemMove();

int main()
{
	testMemSet();
	testMemCpy();
	testMemMove();
	
	return 0;
}

void testMemSet()
{
	char *test_str = NULL;
	
	
	test_str = (char *)calloc(70, sizeof(char));	
	test_str += 1;
	test_str = (char *)MemSet(test_str, '.', 65);
	
	printf("\nnew string using MemSet: %s\n", test_str);
	test_str -= 1;

	free(test_str);
	test_str = NULL;
}

void testMemCpy()
{
	char *dest_str = NULL;
	char source_str[] = "123456789xxxxxxxxxx123456789rrrrr123456789";
	
	dest_str =  (char *)calloc(70, sizeof(char));	
	dest_str += 1;
	dest_str = MemCpy(dest_str, source_str, 42);
	printf("\nnew string using MemCpy:%s\n", dest_str);
	
	dest_str -= 1;
	free(dest_str);
	dest_str = NULL;
}

void testMemMove()
{
	char str[32]="123456789";
	short length_str = 0;

	length_str = strlen(str) + 1;
	
	MemMove(str + 5, str, length_str);
	printf("\nstring result: %s\n", str);
	
}

