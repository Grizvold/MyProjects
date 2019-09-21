#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */
#include <assert.h> /* assert */

static char *Itoa(int i_number, char *str, int base);
static void SwapString(char *swap_str, size_t length);
static int Atoi(char *num_str, int base);

int main()
{
	
	int num = -256;
	int test_num = 0;
	char *test_string = NULL;
	

	test_string = (char *)calloc(21, sizeof(char));
	assert(NULL != test_string);	
	
	printf("\nnumber: %d\n", num);	
	Itoa(num, test_string, 10);
	printf("\nstring result: %s\n", test_string);

	printf("\nnumber: %d\n", test_num);
	test_num = Atoi(test_string, 10);
	printf("\natoi result number: %d\n", test_num);
	
	free(test_string);
	test_string = NULL;

	return 0;
}

static int Atoi(char *num_str, int base)
{
	int result = 0, is_negative = 1;
	size_t i = 0;
	
	/* check is negative */
	if('-' == num_str[0])
	{
		is_negative = -1;
		i++;
	}

	for(; '\0' != num_str[i]; i++)
	{
		result = result * base + num_str[i] - '0';
	}

	
	return result * is_negative;
}
static char *Itoa(int i_number, char *str, int base)
{
	size_t i = 0;
	int is_negative = 0;	
	
	/* if number was 0 */
	if(0 == i_number)
	{
		*(str + 0) = '0';
		*(str + 1) = '\0';
		return str;		
	}
	
	/* if input number is negative */
	if(0 > i_number)
	{
		is_negative = 1;
		i_number *= -1;	
	}
	
	/* copy digits into string */
	for(i = 0; 0 != i_number; i_number /= base, i++)
	{
		*(str + i) = i_number % base + '0';
	}
	
	/* if number is negative */
	if(is_negative)	
	{
		*(str + i) = '-';
	}

	/* reverse string, since its flipped */
	SwapString(str, (i + is_negative));

	/* add string terminator */
	*(str + i + is_negative) = '\0';

	return str;
}

/* reverse string */
static void SwapString(char swap_str[], size_t swap_str_size)
{
	size_t start = 0, end = swap_str_size - 1;

	for(; start < end; start++, end--)
	{
		*(swap_str + start) ^= *(swap_str + end);
		*(swap_str + end) ^= *(swap_str + start);
		*(swap_str + start) ^= *(swap_str + end);
	}
}





