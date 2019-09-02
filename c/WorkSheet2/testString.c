#include <stdio.h> /* printfscanf */
#include <string.h> /* strcmp/strcpy/strcat/strlen  */
#include "String.h" /* StrLen/StrCmp/StrCpy/StrCat */
#include <stdlib.h> /* atoi(string argument to int) */

int main(int  argc, char **argv)
{
	/* definition of our commandline input string1 string2 num */
	char *string_num_1 = NULL, *string_num_2 = NULL, *string_number = NULL;
	int usr_input = 10;
	int num_for_strings = 0;
	/*char *temp_string;*/

	/* get input from command line or declare yourself */
	string_num_1 = argv[1];
	string_num_2 = argv[2];
	string_number = argv[3];
	/* int atoi(const char *str) -> converts string argument str to an integer */
	num_for_strings = atoi(string_number);
	/* end of command line  */

	/*
	string_num_1 = "";
	string_num_2 = "";
	*/

	/* function menu with command line input */
	while((argc > 0) && (usr_input != 0))
   	{
        printf("\n%*c Worksheet2 Menu:\n", 5, ' ');
	printf("%*c 0. To Exit and Stop\n", 5, ' ');
        printf("%*c 1. To strlen\n", 5, ' ');
        printf("%*c 2. To strcmp\n", 5, ' ');
        printf("%*c 3. To strcpy\n", 5, ' ');
        printf("%*c 4. To strcat\n", 5, ' ');
        printf("%*c 5. To strdup\n", 5, ' ');
	printf("%*c 6. To strncpy\n", 5, ' ');
	
        
        scanf("%d", &usr_input);
        
        switch(usr_input)
		{
            case (1):
		printf("%*c    (strlen)The lenght of str1 = %ld and str2 = %ld\n\n\n\n\n", 5, ' '
								, strlen(string_num_1)
								, strlen(string_num_2));
		printf("%*c    (StrLen)The lenght of str1 = %ld and str2 = %ld\n\n\n\n\n", 5, ' '
								, StrLen(string_num_1)
								, StrLen(string_num_2));
                break;
            case (2):
		printf("%*c    (strcmp)The result of strcmp is %d\n", 5, ' ', strcmp(string_num_1, string_num_2));
                printf("%*c    (StrCmp)The result of StrCmp is %d\n", 5, ' ', StrCmp(string_num_1, string_num_2));
                break;
            case (3):
		printf("%*c    (StrCpy)The result of StrCpy is %s\n", 5, ' ', StrCpy(string_num_1, string_num_2));    
		printf("%*c    (strcpy)The result of strcpy is %s\n", 5, ' ', strcpy(string_num_1, string_num_2));    
                break;
            case (4):
		printf("%*c    (strcat)The result of strcat is %s\n", 5, ' ', strcat(string_num_1, string_num_2));          
		printf("%*c    (StrCat)The result of StrCat is %s\n", 5, ' ', StrCat(string_num_1, string_num_2));     
                break;
	    case (5):
		/*temp_string = strdup(string_num_1);
		printf("%*c    (strdup)The result of strdup is %s\n", 5, ' ', temp_string); */
		/*printf("%*c    (strdup)The result of strdup is %s\n", 5, ' ', strdup(string_num_1));         */
		printf("%*c    (StrDup)The result of StrDup is %s\n", 5, ' ', StrDup(string_num_1));
		break;
	    case (6):
		printf("%*c    (StrNCpy)The result of StrNCpy is %s\n", 5, ' ', StrNCpy(string_num_1
											, string_num_2
											, num_for_strings));
            	break;
	    default:
                break;
       		}
    	}
	/* end of menu and command line input */

	

	return 0;
}
