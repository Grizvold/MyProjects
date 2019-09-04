#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */

#include <string.h> /* delim check */

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

/* strncmp Implementation 										  */
/* run on strings and compare if they differ of second string num bytes of first_string and second_string */ 
/* return the difference (ASCII difference)								  */
int StrNCmp(const char *first_string, const char *second_string, size_t num)
{
	while(num--)
	{
		if(*first_string++ != *second_string++)
		{
			return (*(first_string - 1) - *(second_string - 1));
		}
	}

	return 0;	
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
		/* bring destination string to the end(points to empty cell) */
		destination_string = destination_string + StrLen(destination_string);
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

/* strncat Implementation  								*/ 
/* add the [num] number of elemets from source string to the end of destination string	*/
/* returns destination string 								*/ 
char *StrNCat(char *destination_string, const char *source_string, size_t num)
{
	char *string_result = destination_string;
	if (('\0' != *destination_string) && ('\0' != *source_string))
	{
		/* bring destination string to the end(points to empty cell) */
		destination_string = destination_string + StrLen(destination_string);
		/* copy  [num] elements from source string to end of destination string */
		while('\0' != *source_string && num)
		{
			*destination_string++ = *source_string++;
			num--;
		}
		 *destination_string = '\0';
	}
	
	return string_result;
}

/* strstr Implementation								 */ 
/* function  finds  the first occurrence of the substring needle in the string haystack. */
/* return a pointer to the beginning of the located substring, or NULL if the		 */
/* substring is not found. 								 */
char *StrStr(const char *haystack, const char *needle)
{
	const char *iterator_haystack =  haystack, *iterator_needle = needle;
	/* run untill end of haystack */
	while(*iterator_haystack)
	{
		/* when match between 1 char has been found -> perform block check	*/
		/* of size needle between haystack and needle 				*/
		if((*iterator_needle == *iterator_haystack) && (0 == StrNCmp(iterator_haystack, iterator_needle, StrLen(iterator_needle))))
		{
			return (char *)iterator_haystack;
		}

		iterator_haystack++;
	}

	return NULL;
}

/* strspn Implementation 								*/
/* func calc the lenght of the initial substring of string pointed to by first_string	*/ 
/* that is made up of only chars that are in second_string 				*/
/* return the lenght of substring							*/			
size_t StrSpn(const char *first_string, const char *second_string)
{
	size_t num = 0;
	const char *iterator = NULL;

	while(*first_string)
	{
		for(iterator = second_string; (*iterator) && (*iterator != *first_string); iterator++)
		{
			;
		}

		if(!*iterator)
		{
			break;
		}
		
		num++;
		first_string++;
	}

  	return num;
}

/* strcspn Implementation					*/
/* function computes the length of the maximum initial segment	*/
/* of the string pointed to by s1 which consists entirely	*/
/* of characters not from the string pointed to by s2		*/
/* returns the length of the segment.  				*/
size_t StrCSpn(const char *s1, const char *s2)
{
    size_t ret=0;
    while(*s1)
        if(strchr(s2,*s1))
            return ret;
        else
            s1++,ret++;
    return ret;
}


/* strtok Implementation 							*/
/* function  breaks a string into a sequence of zero or more nonempty tokens.	*/
/* returns pointer to the next token, or NULL if there are no more tokens.	*/
char *StrTok(char *str, const char* delim) 
{
	static char *p = 0;

	if(str)
	{
		p = str;
	}
	else if(!p)
	{
       		return 0;
	} 
	
	str = p + StrSpn(p, delim);
	p = str + StrCSpn(str, delim);
	if(p==str)
	{
        	return p=0;
	}

	if(*p)
	{
		*p = 0;
		p++;
	}
    	
    	return str;
}
