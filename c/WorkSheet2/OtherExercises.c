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


/* func runs from [from] to [to] and every num tht has "7"	*/
/* , devisible by 7 with no remainder, replace with BOOM	*/
void BOOM(int from, int to)
{
	int number = 0; 
	const int digit = 7;  
	int temp_num = 0;
	int last_digit = 0;
	char boom_str[] = "BOOM";

	for(number = from; number <= to; number++)
	{
		temp_num = number;
		/* if has 7 digit inside */
		while(temp_num != 0)
		{
			last_digit = temp_num % 10; /* last digit of num */
			temp_num = temp_num / 10;
			
			if(last_digit == digit)
			{
				break;
			}
		}

		/* devided by 7 without reminder */
		if(number%7 == 0 || last_digit == digit)
		{
			puts(boom_str);
		}
	
		else 
		{
			printf(" %d ", number);		
		}
	}

}

/* swap between 2 pointers */
void PointerSwap(int **ptr1, int **ptr2)
{
	int *temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

/* removes unneeded spaces from string */
void RmSpaces(char *str)
{
	char *iterator = str;
	char *my_char = "$";
	char *current = NULL;
	size_t count = 0, count2 = 0;

	/* remove req_char from start of string */
	iterator = iterator + strspn(iterator, my_char);
	strcpy(str, iterator);

	/* remove unneeded space from the [text body] */
	/*while(*iterator++ != '\0')
	{*/
		/* move +1 to add [my_char] between words (space) */
		count = strcspn(str, my_char) + 1;
		printf("\ncount func \n%ld\n", count);
		printf("\niterator func \n%s\n", iterator);

		iterator = iterator + count;
		strcpy(str + count, iterator);
		printf("\niterator func \n%s\n", iterator);

		

		/* run on unneeded spaces untill word */ 
		/*iterator = iterator + strspn(iterator, my_char);
		current = iterator; 
		strcpy(current, iterator);
		strcpy(str + count, current);*/

	/*}*/
	
	printf("\nInside func \n%s\n", str);
}

int main()
{
	char rm_spaces_string[] = "$$$Ruslan$$$$Gor$$Final$$$";
	char *ptr_spaces = rm_spaces_string;
	
	printf("\nBefore func \n%s\n", ptr_spaces);
	RmSpaces(ptr_spaces);
	printf("\nAfter func \n%s\n", ptr_spaces);
	
/*
	char usr_string_palindrom[] = "pollop"; 
	int res = 0;
	int startBOOM = 0, endBOOM = 70;
	int *p_1 = NULL, *p_2 = NULL;
*/
	
/*
	res =  IsPalindrome(usr_string_palindrom);
	printf("\n the ret from IsPalindrome is %d \n", res);

	BOOM(startBOOM, endBOOM);
	
	p_1 = &startBOOM;
	p_2 = &endBOOM;
	printf("\nBefore swap: 1st %p, 2nd %p\n", (void*)p_1, (void*)p_2);
	PointerSwap(&p_1, &p_2);
	printf("\nAfter swap: 1st %p, 2nd %p\n", (void*)p_1, (void*)p_2);
*/
	

	return 0;
}
