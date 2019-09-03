#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */

/* strlen Implementation 			*/
/* Counting string elements untill we reach \0	*/
/* return size_t sizeofstring 			*/
size_t StrLen(const char *tested_string)
{
	const char *string_iterator = tested_string;
	while('\0' != *string_iterator)
	{
		string_iterator++;
	}

	return (string_iterator - tested_string); 
}

/* strcmp Implementation 										  */
/* run on strings and compare if they differ 								  */ 
/* return the difference (ASCII difference)								  */
int StrCmp(const char *first_string, const char *second_string)
{
	while(*first_string && *second_string)
	{
		/* if characters differ or end of second string is reached */
		if (*first_string != *second_string)
			break;
		
		first_string++;
		second_string++;
	}
	/* can also return *first_string - *second_string (int value) */
	/*return *(const unsigned char*)first_string - *(const unsigned char*)second_string;*/
	return (*first_string - *second_string);
}

/* strcasecmp Implementation 					 	    */
/* compares 2 strings without sensibility to cases by using xor for letters */
/* return the difference (ASCII difference)			            */
int StrCaseCmp(const char *first_string, const char *second_string)
{
	while(*first_string && *second_string)
	{
		/* XOR wtih 32 to change the 6th bit. 65 = 'A'=0100 0001 97='a'=0110 0001 */
		/* 32=0010 0000								  */
		/* by changing 6th bit you -32 or +32. A>a, a>A				  */	
		if (*first_string == *second_string || (*first_string ^ 32) == *second_string)
			;
		else
			break;

		first_string++;
		second_string++;
	}
	return (*first_string - *second_string);
}


/* strcpy Implementation 				*/
/* copies the source string to destination string	*/
/* returns destination string 				*/ 
char *StrCpy(char *destination_string, const char *source_string)
{
	char *string_result = destination_string;
	if (('\0' != *destination_string) && ('\0' != *source_string))
	{
		while('\0' != *source_string)
		{
			*destination_string++ = *source_string++;
		}
		/* put NULL termination so it doesnt point to our string anymore */
		*destination_string = '\0';
	}
	
	return string_result;
}

/* strncpy Implementation 									*/
/* function copies src to the buffer pointed to by dest. most n  bytes  of  src  are copied.	*/
/* return  destination string !!If  there is no null byte among the first n bytes of src, 	*/
/* the string placed in dest will not be null-terminated. 					*/
char *StrNCpy(char *destination_string, const char *source_string, size_t num)
{
	char *intr = destination_string;
	if (('\0' != *intr) && ('\0' != *source_string))
	{
	/* copy n elements from source string to destination string*/
		while(('\0' != *source_string) && num-- )
		{
			*intr++ = *source_string++;
		}
		/* put end to the destination string */
		*intr = '\0';
	}

	return destination_string;
}

/*  strchar Implementation											*/
/* function returns a pointer to the first occurrence of the character search_char in the string source_string. */
char *StrChr(const char *source_string, int search_char)
{
	while(*source_string != (char)search_char)
	{
		if (!*source_string)
		{
			return NULL;
		}

		source_string++;
	}

	return (char *)source_string;
}

/* strdup Implementation 					*/
/* duplicate a string to a dynamic obtained memory using malloc	*/
/* returns pointer to the duplicated string 			*/
char *StrDup(const char *source_string)
{
	const char *iterator = source_string;
	char *destination_string = NULL;

	destination_string = (char *) malloc(StrLen(iterator)+1);	

	/* copy the source string to allocated memory */
	while('\0' != *iterator)
	{
		*destination_string++ = *iterator++;
	}
	 *destination_string = '\0';
 
	return (destination_string - (destination_string - source_string));
}

/* strcat Implementation 					*/
/* add the source string to the end of destination string	*/
/* returns destination string 					*/ 
char *StrCat(char *destination_string, const char *source_string)
{
	char *string_result = destination_string;
	if (('\0' != *destination_string) && ('\0' != *source_string))
	{
		/* run untill the end of destination_string */
		while('\0' != *destination_string)
		{
			destination_string++;
		}
		/* copy source string starting from the end NULL of dest */
		while('\0' != *source_string)
		{
			*destination_string++ = *source_string++;
		}
		/* put NULL termination */
		*destination_string = '\0';
	}
	
	return string_result;
}


