#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */
#include "Mem.h" /* memcpy/memset/memmove */

void testMemSet();
void testMemCpy();

int main()
{
	/*testMemSet();*/

	testMemCpy();
	
	return 0;
}

void testMemSet()
{
	char *test_str = NULL;
	
	
	test_str = (char *)calloc(70, sizeof(char));	
	test_str += 1;
	test_str = (char *)MemSet(test_str, '.', 64);
	
	printf("\nnew string: %s\n", test_str);
	test_str -= 1;

	free(test_str);
	test_str = NULL;
}

void testMemCpy()
{
	char *dest_str = NULL;
	char source_str[] = "abc";
	
	dest_str =  (char *)calloc(70, sizeof(char));	
	/*dest_str += 1;*/
	dest_str = MemCpy(dest_str, source_str, 3);
	printf("\n%s\n", dest_str);
	
	/*dest_str -= 1;*/
	free(dest_str);
	dest_str = NULL;
}
