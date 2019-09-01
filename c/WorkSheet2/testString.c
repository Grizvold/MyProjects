#include <stdio.h>
#include "String.h"

int main(int  argc, char **argv)
{
	char *string_num_1 = '\0', *string_num_2 = '\0';  
	int usr_input = 10;
	/* get input from command line or declare yourself */
	string_num_1 = argv[1];
	string_num_2 = argv[2];
	/*
	string_num_1 = "";
	string_num_2 = "";
	*/

	
	while((argc > 0) && (usr_input != 0))
    	{
        printf("%*c Worksheet2 Menu:\n", 5, ' ');
	printf("%*c 0. To Exit and Stop\n", 5, ' ');
        printf("%*c 1. To strlen\n", 5, ' ');
        printf("%*c 2. To strcmp\n", 5, ' ');
        printf("%*c 3. To strcpy\n", 5, ' ');
        printf("%*c 4. To strcat\n", 5, ' ');
        
        scanf("%d", &usr_input);
        
        switch(usr_input)
		{
            case (1):
		printf("%*c    The lenght of str1 = %ld and str2 = %ld\n\n\n\n\n", 5, ' ',
								 StrLen(string_num_1)
								, StrLen(string_num_2));
                break;
            case (2):
                printf("%*c    The result of strcmp is %d\n", 5, ' ', StrCmp(string_num_1, string_num_2));
                break;
            case (3):
		string_num_1 = StrCpy(string_num_1, string_num_2);
                printf("%*c    The result of strcpy is %s\n", 5, ' ', string_num_1);               
                break;
            case (4):
		string_num_1 = StrCat(string_num_1, string_num_2);
                printf("%*c    The result of strcat is %s\n", 5, ' ', string_num_1);            
                break;
            default:
                break;
       		}
    	}

	return 0;
}
