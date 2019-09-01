#include <stdio.h>
#include <stdlib.h>


void print_HelloWorld_in_Hexa()
{
	char arr[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x22};
	printf("\n%s\n\n\n\n\n", arr);
}


float ten_pow_number(int user_num)
{
   float result = 1;
   
   for(int i = 0; (i * i) < (user_num * user_num); i++)
   {
       result = result * 10;
   }
   
   /* negative pow */ 
   if(user_num < 0)
          result = 1 / result;

    return result;
       
}

void number_flip(int *num)
{
    int flipped_num = 0, shaarit = 0, original_num = 0;
    
    original_num = *num;
    while(original_num > 0)
    {
        shaarit = original_num % 10;
        flipped_num = (flipped_num * 10) + shaarit;
        original_num = original_num / 10;
    }
    
    *num = flipped_num;
}

void swap_between2Numers(int *num1, int *num2)
{
    int temp = 0;
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void worksheet1_menu()
{
    int usr_input = 10;
    int usr_pow = 0; 
    float resultOfPow = 0;
    int flip_num = 0;
    int swap_num1 = 0, swap_num2 = 0;
    
    
   /* Menu options of the program, '0' to exit */
   while(usr_input != 0)
    {
        printf("%*c Worksheet1 Menu:\n", 5, ' ');
        printf("%*c 1. Print Hello World in hex\n", 5, ' ');
        printf("%*c 2. Func that receives int and returns 10^number (no pow usage)\n", 5, ' ');
        printf("%*c 3. Func to flip your number\n", 5, ' ');
        printf("%*c 4. Func to swap between 2 numbers\n", 5, ' ');
        
        scanf("%d", &usr_input);
        
        switch(usr_input){
            case (1):
                print_HelloWorld_in_Hexa();
                break;
            case (2):
                printf("%*c    Enter your number to perform 10^number\n", 5, ' ');
                scanf("%d", &usr_pow);
                resultOfPow = ten_pow_number(usr_pow);
                printf("%*c    The result of 10^%d = %f\n\n\n\n\n", 5, ' ', usr_pow, resultOfPow);
                break;
            case (3):
                printf("%*c    Enter the number you want to swap\n", 5, ' ');
                scanf("%d", &flip_num);
                number_flip(&flip_num);
                printf("%*c    The flipped number is %d\n\n\n\n\n", 5, ' ', flip_num);
                break;
            case (4):
                printf("%*c    Enter 2 numbers you want to swap between them\n", 5, ' ');
                scanf("%d %d", &swap_num1, &swap_num2);
                swap_between2Numers(&swap_num1, &swap_num2);
                printf("%*c    The result of swap is num1 now %d, num2 now %d\n\n\n\n\n", 5, ' ', swap_num1, swap_num2);
                break;
            default:
                break;
        }
    }
    
    printf("\n Goodbye! :) \n");
}

/* worksheet1 exercises */ 
int main()
{

	worksheet1_menu();

	return 0;
}
