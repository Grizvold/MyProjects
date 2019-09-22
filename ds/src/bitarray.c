#include "bitarray.h"
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

static size_t word_size = sizeof(size_t);
static void SwapString(char *str, size_t str_size);

/* count bits that are set to '1' */
size_t BitArrCountOn(bit_array_t bit_arr)
{
	size_t i = 0;
	size_t counter = 0;

	bit_arr = ~bit_arr;
	
	for(i = 0; 0 != bit_arr; i++)
	{
		if (0 == (bit_arr & 0x01))
		{
			counter++;
		} 
		
		bit_arr >>= 1;
	}
	
	return (word_size - counter);
}

/* count bits that are set to '0' */
size_t BitArrCountOff(bit_array_t bit_arr)
{
	size_t i = 0;
	size_t counter = 0;

	for(i = 0; 0 != bit_arr; i++)
	{
		if (0 == (bit_arr & 0x01))
		{
			counter++;
		} 
		
		bit_arr >>= 1;
	}
	
	return (counter + (word_size - i));
}

/* perform "bit reversal" on our value */
bit_array_t BitArrMirror(bit_array_t bit_arr)
{
	bit_array_t mirror_num = 0;
	size_t i = 0;
	
	for(i = 0; i < word_size/2; i++)
	{
		mirror_num <<= 1;
		mirror_num |= bit_arr & 1;
		bit_arr >>= 1;
	}
	
	return mirror_num;
}

/* check spesific bit value, if '1' */
int BitArrIsOn(bit_array_t bit_arr, int index)
{
	int is_on = 0;
	size_t i = 0;
	
	bit_arr >>= (index - 1);

	return (bit_arr & 0x01);	
}

/* check spesific bit value, if '0' */
int BitArrIsOff(bit_array_t bit_arr, int index)
{
	int is_on = 0, result = 0;
	size_t i = 0;
	
	bit_arr >>= (index - 1);
	bit_arr &= 0x01;
	
	if(0 == bit_arr)
	{
		result = 1;
	}

	return result;	
}

/* set all elements in bit_arr to '1' */
bit_array_t BitArrSetAll(bit_array_t bit_arr)
{
	return ~0;
}

/* set all elements in bit_arr to '0' */
bit_array_t BitArrResetAll(bit_array_t bit_arr)
{
	return 0;
}

/* put elements in bit_arr into string */
char *BitArrToString(bit_array_t bit_arr, char *str)
{
	size_t i = 0;
	
	/* check if str is not null */
	assert(NULL != str);
	
	for(i = 0; i < word_size; i++)
	{
		*(str + i) = bit_arr % 2 + '0';
	}
	
	SwapString(str, (i));
	
	*(str + i) = '\0';
	
	return str;
}

static void SwapString(char *str, size_t str_size)
{
	size_t start = 0, end = str_size - 1;
	
	for(; start < end; start++, end--)
	{
		*(str + start) ^= *(str + end);
		*(str + end) ^= *(str + start);
		*(str + start) ^= *(str + end);
	}
}

/* flip the value of element in spesific position */
bit_array_t BitArrFlip(bit_array_t bit_arr, int index)
{
	bit_array_t specific_bit = 1;
	
	specific_bit <<= index;
	bit_arr ^= specific_bit;
	
	return bit_arr;
}

/* set the value of element in spesific position to '1' */
bit_array_t BitArrSetOn(bit_array_t bit_arr, int index)
{
	bit_array_t specific_bit = 1;
	
	specific_bit <<= index;
	bit_arr |= specific_bit;
	
	return bit_arr;
}

/* set the value of element in spesific position to '0' */
bit_array_t BitArrSetOff(bit_array_t bit_arr, int index)
{
	bit_array_t specific_bit = 1;
	
	specific_bit <<= index;
	specific_bit = ~specific_bit;
	bit_arr &= specific_bit;
	
	return bit_arr;
}

/* set the value of element in spesific position to val */
bit_array_t BitArrSet(bit_array_t bit_arr, int index, int val)
{
	bit_array_t specific_bit = 1;
	
	specific_bit <<= index;
	/* check if val is 0 or 1 */
	if(0 == val)
	{
		specific_bit = ~specific_bit;
		bit_arr &= specific_bit;
	}
	
	else if(1 == val)
	{
		bit_arr |= specific_bit;
	}
	
	return bit_arr;
}


bit_array_t BitArrRotR(bit_array_t bit_arr, size_t num_rotations)
{
	bit_array_t temp = 0;
	
	num_rotations %= word_size;
	temp = (bit_arr << (word_size - num_rotations));
	bit_arr >>= num_rotations;

	return (bit_arr | temp);
}

bit_array_t BitArrRotL(bit_array_t bit_arr, size_t num_rotations)
{
	bit_array_t temp = 0;
	
	num_rotations %= word_size;
	temp = (bit_arr >> (word_size - num_rotations));
	bit_arr <<= num_rotations;

	return (bit_arr | temp);
}
