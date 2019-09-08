#include <stdio.h> /* printf */

void PrintSizeOf()
{

  int arr[5] = {0};

  printf("sizeof(char) 			== %ld\n", sizeof(char));
  printf("sizeof(short)	 		== %ld\n", sizeof(short));
  printf("sizeof(unsigned char)	 	== %ld\n", sizeof(unsigned char));
  printf("sizeof(signed char)	 	== %ld\n", sizeof(signed char));
  printf("sizeof(int) 			== %ld\n", sizeof(int));
  printf("sizeof(long) 			== %ld\n", sizeof(long));
  printf("sizeof(float) 			== %ld\n", sizeof(float));
  printf("sizeof(double) 			== %ld\n", sizeof(double));
  printf("sizeof(long double) 		== %ld\n", sizeof(long double));

  printf("\nsizeof(char*) 		== %ld\n", sizeof(char*));
  printf("sizeof(int*) 		== %ld\n", sizeof(int*));
  printf("sizeof(short*)	 	== %ld\n", sizeof(short*));
  printf("sizeof(long*) 		== %ld\n", sizeof(long*));

  printf("\nsizeof(int arr[5])		== %ld\n", sizeof(arr));
}

/* Print Data types */
int main()
{
	PrintSizeOf();

	return 0;
}

