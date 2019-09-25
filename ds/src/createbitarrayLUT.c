#include <stdio.h> /* fopen */

#define LUT_size  256

typedef size_t bit_arr_t;

static size_t word_size = sizeof(bit_arr_t);

static void CreateBitArrLUT();
static size_t BitArrCountOn(bit_arr_t bit_arr);
bit_arr_t BitArrMirror(bit_arr_t bit_arr);
bit_arr_t BitArrSet(bit_arr_t bit_arr, int index, int val);

int main()
{
	CreateBitArrLUT();

	return 0;
}

/* creates 2 LUTs inside file */
static void CreateBitArrLUT()
{
	size_t i = 0;
	size_t bits_on = 0;
	FILE *ptr_bit_arr_LUT = NULL;
	char *name_of_file = "bit_arr_LUT.c";
	
	ptr_bit_arr_LUT = fopen(name_of_file, "w");
	if(NULL == ptr_bit_arr_LUT)
	{
		fprintf(stderr, "error opening %s", name_of_file);
		perror(name_of_file);

		return;
	}
	
	fprintf(ptr_bit_arr_LUT, "%s", "int bitOn_arr_LUT[256] = {\n");
	/* fill the values in bit count LUT */
	for(i = 0; i < LUT_size; i++)
	{
		if(i == (LUT_size - 1))
		{
			bits_on =  BitArrCountOn(i);
			fprintf(ptr_bit_arr_LUT, "%ld", bits_on);		
		}
		else
		{
			fprintf(ptr_bit_arr_LUT, "%ld,", BitArrCountOn(i));
		}
		/* every 8 values jump to new line for readability */
		if(0 == (i % 8))	
		{
			fprintf(ptr_bit_arr_LUT, "\n");	
		}		
	
	}

	fprintf(ptr_bit_arr_LUT, "%s\n\n", "};");

	/* start bit mirror LUT */
	fprintf(ptr_bit_arr_LUT, "%s", "int bitarr_mirror_LUT[256] = {\n");
	
	/* fill the values in mirror LUT */
	for(i = 0; i < LUT_size; i++)
	{
		if(i == (LUT_size - 1))
		{
			bits_on =  BitArrMirror(i);
			fprintf(ptr_bit_arr_LUT, "%ld", bits_on);		
		}
		else
		{
			fprintf(ptr_bit_arr_LUT, "%ld,", BitArrMirror(i));
		}
		/* every 8 values jump to new line for readability */
		if(0 == (i % 8))	
		{
			fprintf(ptr_bit_arr_LUT, "\n");	
		}		
	
	}
	
	fprintf(ptr_bit_arr_LUT, "%s", "};");

	if(0 == fclose(ptr_bit_arr_LUT))
	{
		ptr_bit_arr_LUT = NULL;
		printf("\nFile %s was successfully closed\n", name_of_file);
	}		
}

static size_t BitArrCountOn(bit_arr_t bit_arr)
{
	size_t i = 0;
	size_t counter = 0;
	size_t mask = 0x01; /* check last bit */

	bit_arr = ~bit_arr;
	
	for(i = 0; 0 != bit_arr; i++)
	{
		if (0 == (bit_arr & mask))
		{
			counter++;
		} 
		
		bit_arr >>= 1;
	}
	
	return counter;
}

/* set the value of element in spesific position to val */
bit_arr_t BitArrSet(bit_arr_t bit_arr, int index, int val)
{
	bit_arr_t specific_bit = 1;
	
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

/* perform "bit reversal" on our value */
bit_arr_t BitArrMirror(bit_arr_t bit_arr)
{
	bit_arr_t mask_r = 1;
	bit_arr_t mask_l = 1;
	int first = 0, last = 0;
	size_t i = 0;

	mask_l <<= (word_size - 1); /* mask_l is pushed left to msb */	

	for (i = 0; i < word_size / 2 ; i++)
	{
		first = ((bit_arr & mask_r) == mask_r); 
		last = ((bit_arr & mask_l) == mask_l); 
		
		bit_arr = BitArrSet(bit_arr, i, last); 
		bit_arr = BitArrSet(bit_arr, (word_size - i - 1), first); 
		
		mask_r <<= 1; /* forward mask_r to left bit */
		mask_l >>= 1; /* forward mask_l to right bit */
	}
		
	return bit_arr;
}
