#include <stddef.h> /* size_t */

/******************************************************************************/
/*                      Internal Functions Declaration                        */
/******************************************************************************/
static char *ReverceRecHelper(char *str, size_t right_iter, size_t left_iter);
static void CharSwap(char *x, char *y);
/******************************************************************************/

size_t StrLenRec(const char *str)
{
    return ('\0' == *str) ? 0 : 1 + StrLenRec(++str);
}

char *StrCpyRec(char *dest, const char *src)
{
    *dest = *src;

    if('\0' != *src)
    {
        StrCpyRec(dest + 1, src + 1);
    }

    return dest;
}

int StrCmpRec(const char *str1, const char *str2)
{
    if(*str1 != *str2 || '\0' == *str1)
    {

        return (*str1 - *str2);
    }
    else
    {
        StrCmpRec(str1 + 1, str2 + 1);
    }
}

char *StrStrRec(const char *haystack, const char *needle)
{
    /* if we reached end of main string */
    if('\0' == *haystack)
    {
        return NULL;
    }
    /* in case substring isnt found in main string keep searching */
    else if (*haystack != *needle)
    {
        StrStrRec(++haystack, needle);
    }
    /* in case substring is found, keep running on both of them */
    else
    {
        StrStrRec(haystack + 1, needle + 1);
        return (char *)haystack;
    }
    
}

char *StrReverceRec(char *str)
{
    return ReverceRecHelper(str, 0, StrLenRec(str) - 1);    
}

size_t Fibonacci(size_t index)
{
    if(index <= 1)
    {
        return index;
    }
    
    return Fibonacci(index - 1) + Fibonacci(index - 2);
}

/******************************************************************************/
/*                      Internal Functions Definition                         */
/******************************************************************************/
static char *ReverceRecHelper(char *str, size_t right_iter, size_t left_iter)
{
    if(right_iter >= left_iter)
    {
        return str;
    }

    CharSwap(str + right_iter, str + left_iter);

    return ReverceRecHelper(str, ++right_iter, --left_iter);
 }

 static void CharSwap(char *x, char *y)
 {
     char temp = *x;
     *x = *y;
     *y = temp;
 }
/******************************************************************************/
