#include <stdio.h> /* fopen */

#define LUT_size  256

typedef size_t bit_arr_t;

static size_t word_size = sizeof(bit_arr_t);

static void CreateBitArrLUT();
static size_t BitArrCountOn(bit_arr_t bit_arr);
static bit_arr_t BitArrMirror(bit_arr_t bit_arr);

int main()
{
	CreateBitArrLUT();

	return 0;
}

/* creates 2 LUTs inside file */
static void CreateBitArrLUT()
{
	size_t i = 0;
	size_t char_counter = 0;
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
	
	fprintf(ptr_bit_arr_LUT, "%s", "int const bitOn_arr_LUT[256] = {\n");
	/* fill the values in bit count LUT */
	for(i = 0; i < LUT_size; i++)
	{
		if(i == (LUT_size - 1))
		{
			bits_on = BitArrCountOn(i);
			fprintf(ptr_bit_arr_LUT, "%ld", bits_on);		
		}
		else
		{
			fprintf(ptr_bit_arr_LUT, "%ld,", BitArrCountOn(i));
		}
		
		char_counter++;
		/* every 8 values jump to new line for readability */
		if(7 < char_counter)		
		{
			fprintf(ptr_bit_arr_LUT, "\n");
			char_counter = 0;	
		}		
	
	}

	fprintf(ptr_bit_arr_LUT, "%s\n\n", "};");

	char_counter = 0;	
	/* start bit mirror LUT */
	fprintf(ptr_bit_arr_LUT, "%s", "int const bitarr_mirror_LUT[256] = {\n");
		
	/* fill the values in mirror LUT */
	for(i = 0; i < LUT_size; i++)
	{
		if(i == (LUT_size - 1))
		{
			bits_on = BitArrMirror(i);
			fprintf(ptr_bit_arr_LUT, "%ld", bits_on);		
		}
		else
		{
			fprintf(ptr_bit_arr_LUT, "%ld,", BitArrMirror(i));
		}
		
		char_counter++;
		/* every 8 values jump to new line for readability */
		if(7 < char_counter)		
		{
			fprintf(ptr_bit_arr_LUT, "\n");
			char_counter = 0;	
		}
	
	}
		
	fprintf(ptr_bit_arr_LUT, "%s\n\n", "};");

	if(0 == fclose(ptr_bit_arr_LUT))
	{
		ptr_bit_arr_LUT = NULL;
		printf("\nFile %s was successfully closed\n", name_of_file);
	}		
}

/* fill LUT of bitOn_arr_LUT */
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

/* fill LUT of bitarr_mirror_LUT */
static bit_arr_t BitArrMirror(bit_arr_t bit_arr)
{
    bit_arr_t mirror_num = 0;
    size_t i = 0;
    
    for(i = 0; i < (word_size); i++)
    {
        mirror_num <<= 1;
        mirror_num |= bit_arr & 1;
        bit_arr >>= 1;
    }
        
    return mirror_num;
}


