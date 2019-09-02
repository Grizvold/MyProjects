#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */

#include <stdio.h>

/* strlen Implementation */
/* Counting string elements untill we reach \0 */
/* return size_t sizeofstring */
size_t StrLen(const char *tested_string)
{
	const char *string_iterator = tested_string;
	while('\0' != *string_iterator)
	{
		string_iterator++;
	}

	return string_iterator - tested_string; 
}

/* strcmp Implementation */
/* run on strings and compare if they differ */ 
/* returns the difference of 2 strings */
int StrCmp(const char *first_string, const char *second_string)
{
	while(*first_string)
	{
		/* if characters differ or end of second string is reached */
		if (*first_string != *second_string)
			break;
		
		/* moving forward to the next characters */
		first_string++;
		second_string++;
	}
	
	/* return the difference (ASCII difference)*/
	return *(const unsigned char*)first_string - *(const unsigned char*)second_string;
}

/* strcpy Implementation */
/* copies the source string to destination string */
/* returns destination string */ 
char *StrCpy(char *destination_string, const char *source_string)
{
	char *string_result = destination_string;
	if (('\0' != *destination_string) && ('\0' != *source_string))
	{
	/* copying src string to dest string */
		while('\0' != *source_string)
		{
			*destination_string++ = *source_string++;
		}
		/* put NULL termination so it doesnt point to our string anymore */
		*destination_string = '\0';
	}
	
	return string_result;
}

/* strncpy Implementation */
/* copies num characters from source string to destination string */ 
/*  returns destination string */
char *StrNCpy(char *destination_string, const char *source_string, size_t num)
{
	/* put our iterator to our destinaiton string */
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

/* strcat Implementation */
/* add the source string to the end of destination string */
/* returns destination string */ 
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

/* strdup Implementation */
/* duplicate a string to a dynamic obtained memory using malloc */
/* returns pointer to the duplicated string */
char *StrDup(const char *source_string)
{
	/* put iterator at the start of our string, and declare pointer for copied string */
	const char *iterator = source_string;
	char *destination_string = NULL;

	/* counting size of source string for malloc declaration */	
	/*while('\0' != *iterator)
		iterator++;*/

	destination_string = (char *) malloc(StrLen(iterator)+1);	
	/* reset iterator to the start of string */ 	
	/*iterator = source_string;*/

	/* copy the source string to allocated memory */
	while('\0' != *iterator)
	{
		*destination_string++ = *iterator++;
	}
	 *destination_string = '\0';
 
	return destination_string - (destination_string - source_string);
}




