#include <stdio.h> /* printf */

/********************** func declaration ***********************/
unsigned int CountSetBits(unsigned int num);
unsigned int DevidedBySixteen(unsigned int n);
unsigned int CountSetBitsNoLoop(unsigned int num);
unsigned int ByteMirror(char num);
int GetBit(char num, int bit_num);
int BitCheck2and6BothOn(unsigned char num);
int BitCheck2and6OneOn(unsigned char num);
int AddOneToInt(unsigned int num);
int CountOnBits(int num);
int IsPowerOfTwo(unsigned int num);
int SwapBit3and5(unsigned int num);
long Pow2(unsigned int x, unsigned int y);
void HasThreeBitsOn(int *num_arr, int size);
void SwapWithXor(unsigned int *num_1, unsigned int *num_2);
void FloatLayOutFunc(float num);
/***************************************************************/

/********************** LUT and struct dec ***********************/
int num_to_bits[16] =  {0, 1, 1, 2, 1, 2, 2, 3,   
                       1, 2, 2, 3, 2, 3, 3, 4}; 
                       
struct FloatLayOut
{
    unsigned int mantisa: 23;
    unsigned int exponen: 8;
    unsigned int sign: 1;
};
/*****************************************************************/

/* x*(2^y) */
long Pow2(unsigned int x, unsigned int y)
{
    x = x << y;
    
    return x;
}

/* is num power of 2*/
int IsPowerOfTwo(unsigned int num)
{
    if( ((num - 1) & num) == 0 )
    {
        return 1;
    }
    
    return 0;
}

/* add 1 to int without arithmetic */
int AddOneToInt(unsigned int num)
{
    unsigned adding_num = 1;
    unsigned carry = 0;
    
    while(adding_num != 0)
    {
        /* getting last bit of num to check for carry */
        carry = num & adding_num;
        
        /* sum num and adding num where */
        /* at least 1 bit is not set    */
        num = num ^ adding_num;
        
        /* shifting carry left so it will give required sum */
        adding_num = carry << 1;
    }
    
    return num;
}

/* print numbers in array that has 3 bits on */
void HasThreeBitsOn(int num_arr[], int size)
{
    int num = 0;
    int i = 0;
    
    for(i = 0; i < size; i++)
    {
        num = num_arr[i];
        if(CountOnBits(num) == 3)
        {
            printf("\n%d has 3 bits on\n", num_arr[i]);
        }
    }
}

/* counting "on" bits*/
int CountOnBits(int num)
{
    int counter = 0;
    
    for(counter = 0; num != 0; num >>= 1)
    {
        if((num & 1) == 1)
        {
            counter++;
        }
    }
    
    return counter;
}

/* byte mirror */
unsigned int ByteMirror(char num)
{
    unsigned int mirror_num = 0;
    int i = 0;
    
    for(i = 0; i < 8; i++)
    {
        mirror_num <<= 1;
        mirror_num |= num & 1;
        num >>= 1;
    }
        
    return mirror_num;
}

/* checks bits 2 and 6 if they both on - true */
int BitCheck2and6BothOn(unsigned char num)
{
    int num_1 = 0, num_2 = 0;
    
    num_1 = GetBit(num, 2);
    num_2 = GetBit(num, 6);
    
    return (num_1 & num_2);
}


/* checks bits 2 and 6 if at least one on - true */
int BitCheck2and6OneOn(unsigned char num)
{
    int num_1 = 0, num_2 = 0;
    
    num_1 = GetBit(num, 2);
    num_2 = GetBit(num, 6);
    
    return (num_1 | num_2);
}

/* swap bit 3 and 5 in number anr return new number */
int SwapBit3and5(unsigned int num)
{
    unsigned int bit_3 = 0, bit_5 = 0, nibble = 0;
    
    bit_3 = (num >> 2) & 1;
    bit_5 = (num >> 4) & 1;

    /* xor between bit 3 and 5 */    
    nibble = bit_3 ^ bit_5;
    /* put those bits to original position */
    nibble = (nibble << 2) | (nibble << 4);
    
    /* swap bit 3 and 5 */
    num = num ^ nibble;
    
    return num;
}

/* flot number layout (mantisa/exponen/sign) */
void FloatLayOutFunc(float num)
{
    struct FloatLayOut *f_ptr = NULL;
    
    f_ptr = (struct FloatLayOut *)(&num);
    printf("\nmantisa is %d\n", f_ptr->mantisa);
    printf("\nexponen is %d\n", f_ptr->exponen);
    printf("\nsign is %d\n", f_ptr->sign);
    
}
                       
/* count set bits in number without loop */
unsigned int CountSetBitsNoLoop(unsigned int num) 
{ 
   int nibble = 0; 
   
   if (0 == num) 
   {
      return num_to_bits[0]; 
   }
  
   /* set nibble to last 4 bits in number */
   nibble = num & 0xf; 
    
    /* use LUT for pre sorted values up to 16 (nibble)              */
    /* and add recursively these values untill we reach end of num  */
    /* by sending every run shifted num by 4 bits                   */
   return num_to_bits[nibble] + 
          CountSetBitsNoLoop(num >> 4); 
} 
  

/* count set bits in number */
unsigned int CountSetBits(unsigned int num)
{
    unsigned int counter = 0;
    
    while(num)
    {
        counter += num & 1;
        num >>= 1;
    }
    
    return counter;
}

/* get spesific bit from number */
int GetBit(char num, int bit_num)
{
    num = num >> ((bit_num) - 1);
    num = num & 1;
    
    return num;
}

/* find closest number to devided by 16 */
unsigned int DevidedBySixteen(unsigned int n)
{
    unsigned int a = 0;
    
    a = n;
    a = a >> 4; /* which is the same as dividing by 16. */
    a = a + 1;
    a = a << 4; /* which is the same as multiplying by 16 */
    
    /* return closest number devided by 16 to n */
    /* that is smaller than n                   */
    if (a > n && n > 16)
        {
            a = a - 16;
        }
        
    return a; 
}

/* swap 2 numbers by uxing xor */
void SwapWithXor(unsigned int *num_1, unsigned int *num_2)
{
    *num_1 = *num_1 ^ *num_2;
    *num_2 = *num_1 ^ *num_2;
    *num_1 = *num_1 ^ *num_2;
}


int main()
{
    unsigned int num = 8, num2 = 4;
    unsigned int num1_swap = 3, num2_swap = 0;
    float f_num = 34.5;
    int arr[5] = {82, 66, 114, 2, 208};
    
    printf("\nmy num %d, closes num devided by 16 is %d\n", num, DevidedBySixteen(num));

    printf("\nfirst num is %d, second num is %d\n", num1_swap, num2_swap);
    SwapWithXor(&num1_swap, &num2_swap);
    printf("\nnow first is %d, second is %d \n", num1_swap, num2_swap);
    
    printf("\nnumber of set bits in %d is %d\n", num, CountSetBits(num));
    
    printf("\nnumber of set bits in %d is %d\n", num, CountSetBitsNoLoop(num));
    
    printf("\nfloat %f lay out is: \n", f_num);
    FloatLayOutFunc(f_num);
    
    printf("\ntest bit %d\n", GetBit(120, 5));
    
    printf("\ncheck bits 2 and 6 in number %d if both on. Result is %d\n", num, BitCheck2and6BothOn(num));
    
    printf("\ncheck bits 2 and 6 in number %d if at least one on. Result is %d\n", num, BitCheck2and6OneOn(num));
    
    printf("\noriginal number is %d, after bits 3 and 5 swaped it's %d \n", num, SwapBit3and5(num));
    
    printf("\noriginal number is %d, and his mirror is %d \n", num, ByteMirror(num));
    
    printf("\nin array the following numbers have 3 bits on:\n");
    HasThreeBitsOn(arr, 5);
    
    printf("\noriginal number is %d, after adding 1 the result is %d \n", num, AddOneToInt(num));

    printf("\nnumber is %d, is it power of 2? %d \n", num, IsPowerOfTwo(num));
    
    printf("\n %d * (2 ^ %d) is %ld\n", num, num2, Pow2(num, num2));
    
    return 0;
}
