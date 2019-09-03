#include "OtherExercises.h"
#include <stddef.h> /* size_t */
#include "String.h" /* StrLen */
int IsPalindrome(const char *test_string)
{	
	size_t i = 0;
	const char *from_begining = test_string;
	const char *from_end = test_string + StrLen(test_string) - 1;

	for(;i < StrLen(test_string) / 2; i++)
	{
		if(from_begining != from_end)
		{
			return 0;
		}
		
		from_begining++;
		from_end--;
	}

	return 1;
}


