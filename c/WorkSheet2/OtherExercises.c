#include <stdio.h> /* size_t */
#include "string.h" /* strlen */

char    SumDigits(char a, char b, int carry, char *sum);
char    *ToLast(char *str);
char    *SumBigNum(const char *str1,const char *str2, char *sum);


char *SumBigNum(const char *str1,const char *str2, char *sum)
{
    int carry = 0;
    char *big_arr = (char *) str1;
    char *small_arr = (char *) str2;
    int small_size;
    int diff_size;
    int i = 0;

    if (strlen(str1) < strlen(str2))
        {
            big_arr = (char *) str2;
            small_arr = (char *) str1;
        }

    small_size = strlen(small_arr);
    diff_size = strlen(big_arr) - small_size;

    small_arr = ToLast(small_arr);
    big_arr = ToLast(big_arr);
    sum = ToLast(sum);

    for(i = 0; i < small_size; i++)
        {
            carry = SumDigits(*big_arr, *small_arr, carry, sum);
            big_arr--;
            small_arr--;
            sum--;
        }

    for(i = 0; i < diff_size; i++)
        {
            carry = SumDigits(*big_arr, '0', carry, sum);
            big_arr--;
            sum--;
        }

    if(carry > 0)
        {
            *sum = carry + '0';
        }

    while('0' == *sum)
    {
        sum++;
    }

    return sum;
}

char SumDigits(char a, char b, int carry, char *sum)
{
    int a_int = a - '0';
    int b_int = b - '0';
    int digit_sum = a_int + b_int + carry;

    if (digit_sum > 10)
        {
            digit_sum = digit_sum % 10;
            *sum = digit_sum + '0';
            return 1;
        }

    *sum = digit_sum + '0';
    
    return 0;
}

char *ToLast(char *str)
{
    while ('\0' != *str)
        {
            str++;
        }
    return str-1;
}




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
/* , devisible by 7 with noc remainder, replace with BOOM	*/
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
    char *dest = str;  
    char char_rm = '$';
    
    /* While we're not at the end of the string, loop... */
    while (*str != '\0')
    {
        /* Loop while the current character is a space, AND the next    */
        /* character is a space                                         */
        while (*str == char_rm && *(str + 1) == char_rm)
            {
                str++;  /* Just skip to next character */   
            }

        /* Copy from the "source" string to the "destination" string,   */   
        /* while advancing to the next character in both                */
       *dest++ = *str++;
    }
    /* Make sure the string is properly terminated */ 
    dest--;
    *dest = '\0';
}



int main()
{
	char rm_spaces_string[] = "$$$$Ruslan$$$$$Gor$$Final$T$$fsdfsd  .$";
	char usr_string_palindrom[] = "pollop"; 
	int res = 0;
	int startBOOM = 0, endBOOM = 70;
	int *p_1 = NULL, *p_2 = NULL;
	
	char *str1 = "1234";
   	 char *str2 = "9999";
   	 char arr[6] = "hello";

	printf("\nBefore func \n%s\n", rm_spaces_string);
	RmSpaces(rm_spaces_string);
	printf("\nAfter func \n%s\n", rm_spaces_string);
	

	
	res =  IsPalindrome(usr_string_palindrom);
	printf("\n the ret from IsPalindrome is %d \n", res);

	BOOM(startBOOM, endBOOM);
	
	p_1 = &startBOOM;
	p_2 = &endBOOM;
	printf("\nBefore swap: 1st %p, 2nd %p\n", (void*)p_1, (void*)p_2);
	PointerSwap(&p_1, &p_2);
	printf("\nAfter swap: 1st %p, 2nd %p\n", (void*)p_1, (void*)p_2);

    	
   	 SumBigNum(str1,str2,arr);
    
   	 printf("%s\n", arr);
	

	return 0;
}
