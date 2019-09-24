#include <stdio.h> /* fopen */
#include <assert.h> /* assert */

#define ARR_SIZE 256

int main()
{
	CreateBitArrLUT();

	return 0;
}

static void CreateBitArrLUT()
{
	int bitOn_arr_LUT[ARR_SIZE] = {0};
	FILE *ptr_bitOn_count_LUT = NULL;
	size_t i = 0;
	
	ptr_bitOn_count_LUT = fopen("countbitOnLUT.txt", "w");
	assert(NULL != ptr_bitOn_count_LUT);
	
	fprintf(ptr_bitOn_count_LUT, "%s", "int bitOn_arr_LUT[256] = {");
	
	for(i = 0; i < ARR_SIZE; i++)
	{
		
	}
}
