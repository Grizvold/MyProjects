#include <stdio.h> /* printf */

long Pow2(unsigned int, unsigned int);


/******** calculating x * (2 ^ y) ********/
long Pow2(unsigned int x, unsigned int y)
{
	unsigned int i = 0;
	unsigned int two_pow_y = 1;
	long result = 0;
	
	/* calculate 2 ^ y */
	for(i = 0; i < y; i++)
	{
		two_pow_y = two_pow_y << 1;
	}

	
	/* multiply x * (y^2) */
	for(i = 0; two_pow_y > 0; i++, two_pow_y /= 2)
	{
		/***** check set bit		*****/ 
		/***** shift x, i times	*****/
		if (two_pow_y % 2 == 1)
		{
			result += x << i;
		}
	}
	
	return result;
}

int main()
{
	int num_1 = 8, num_2 = 3;
	
	printf("\n result of %d * (2 ^ %d) is = %ld \n", num_1, num_2, Pow2(num_1, num_2));

	return 0;
}

