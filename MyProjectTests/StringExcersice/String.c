
/* strlen Implementation */
/* Counting string elements untill we reach \0 */
int StrLen(const char *tested_string)
{
	int i = 0;
	for(i = 0; req_string[i] != '\0'; i++);
	return i; 
}

/* strcmp Implementation */
/* returns the difference of 2 strings */
int StrCmp(const char *first_string, const char *second_string)
{
	while(*first_string)
	{
		/* if characters differ or end of second string is reached */
		if (*first_string != *second_string)
			break;
		
		/* moving forward to the next characters */
		first_string;
		second_string;
	}
	
	/* return the difference */
	return *(const unsigned char*)first_string - *(const unsigned char*)second_string;
}

/* strcpy Implementation */
/* copies the source string to destination string */
/* returns destination string */ 
char *StrCpy(char *destination_string, const char *source_string)
{
	char *string_result = destination_string;
	if ((NULL != destination_string) && (NULL != source_string))
	{
	/* copying src string to dest string */
		while(NULL != *source_string)
		{
			*destination_string ++ = *source_string++;
		}
		/* put NULL termination so it doesnt point to our string anymore */
		*destination_string = NULL;
	}
	
	return string_result;
}

/* strat Implementation */
char *StrCat(chr *destination_string, const char *source_string)
{
	char *string_result = destination_string;
	if ((NULL != destination_string) && (NULL != source_string))
	{
		/* run untill the end of destination_string */
		while(NULL != *destination_string)
		{
			destination_string++;
		}
		/* copy source string starting from the end NULL of dest */
		while(NULL != *source_string)
		{
			*destination_string++ = *source_string++;
		}
		/* put NULL termination */
		*destination_string = NULL;
	}
	
	return string_result;
}
