#include <stdio.h> /* printf */
#include "OtherExercises.h" /*IsPalindrome*/

int main(int  argc, char **argv)
{	
	char *string_input = NULL;

	string_input = argv[1];
	/* check if polindrome */	
	if(IsPalindrome(string_input))
	{
		printf("\n The string %s is polindrom\n", string_input);
	}
	else
	{
		printf("\n The string %s is NOT polindrom\n", string_input);
	}		
	
	return 0;
}
 
