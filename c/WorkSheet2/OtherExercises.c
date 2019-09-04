#include <stdio.h> /* size_t */
#include "string.h" /* StrLen */

/* check if string is palindrome */
int IsPalindrome(const char *test_string)
{	
	size_t i = 0;
	const char *from_begining = test_string;
	const char *from_end = test_string + strlen(test_string) - 1;

	for(i = 0; i < (strlen(test_string) / 2); i++)
	{
		if(*from_begining != *from_end)
		{
			return 0;
		}
		
		from_begining++;
		from_end--;
	}

	return 1;
}

int main()
{
	char usr_string[] = "pollop"; 
	int res = 0;
	
	res =  IsPalindrome(usr_string);
	printf("\n the ret from IsPalindrome is %d \n", res);
	return 0;
}
