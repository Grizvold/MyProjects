#include "bitarray.h" /* bit array func */
#include <stdio.h> /* prtinf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

int main()
{
	bit_arr_t test_arr;	
	char *str = (char *)malloc(65);
	
	assert(NULL != str);

/*	test_arr = BitArrSetAll(test_arr);	
	printf("\n%lu\n", test_arr);	*/

/*	test_arr = BitArrResetAll(test_arr);	
	printf("\n%lu\n", test_arr);	*/
	
/*	test_arr = BitArrSetOn(test_arr, 15);	
	printf("\n%lu\n", test_arr);	*/
	
/*	test_arr = BitArrSetOff(test_arr, 15);
	printf("\n%lu\n", test_arr);	*/
	
/*	test_arr = BitArrSetOn(test_arr, 15);
	printf("\n%lu\n", test_arr);
	test_arr = BitArrFlip(test_arr, 15);
	printf("\n%lu\n", test_arr);	*/
	
/*	test_arr = BitArrSet(test_arr, 15, 1);
	printf("\n%lu\n", test_arr);
	test_arr = BitArrSet(test_arr, 15, 0);
	printf("\n%lu\n", test_arr);	*/
	
/*	test_arr = BitArrSet(test_arr, 15, 1);
	printf("\n%lu\n", test_arr);
	printf("\nIs on: %d\n", BitArrIsOn(test_arr, 15));
	
	test_arr = BitArrSet(test_arr, 15, 0);
	printf("\n%lu\n", test_arr);	
	printf("\nIs off: %d\n", BitArrIsOff(test_arr, 15));	*/
	
/*	test_arr = 57552;
	test_arr = BitArrMirror(test_arr);
	printf("\n%lu\n", test_arr);	*/
	
/*	test_arr = 892453;
	str = BitArrToString(test_arr, str);
	printf("\n%lu\n", test_arr);
	printf("\nstring is %s\n", str);	*/
	
/*	test_arr = 892453;
	printf("\n%lu\n", BitArrCountOn(test_arr));
	printf("\n%lu\n", BitArrCountOff(test_arr));	*/
	
	test_arr = 892453;
	test_arr = BitArrRotR(test_arr, 5);
	test_arr = BitArrRotL(test_arr, 5);
	printf("\n%lu\n", test_arr);
	
	
	
	
	
	return 0;
}

