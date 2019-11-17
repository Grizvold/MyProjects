#include <stddef.h> /* size_t */

size_t StrLenRec(const char *str)
{
    if('\0' == *str)
    {
        return 0;
    }

    else
    {
        return 1 + StrLenRec(++str);
    }
    
}

char *StrCpyRec(char *dest, const char *src)
{
    if('\0' == *src)
    {
        *dest = *src;

        return dest;
    }

    else
    {
        *dest = *src;
        StrCpyRec(dest + 1, src + 1);
    }
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
    if('\0' == *haystack)
    {
        return NULL;
    }
    else if (*haystack != *needle)
    {
        StrStrRec(++haystack, needle);
    }
    else
    {
        StrStrRec(haystack + 1, needle + 1);
        return (char *)haystack;
    }
    
}

char *ReverceRec(char *str)
{
    return ReverceRecHelper(str, StrLenRec(str), 0);    
}

char *ReverceRecHelper(char *str, size_t right_iter, size_t left_iter)
{
    char temp = '\0';

    if(right_iter >= left_iter)
    {
        return str;
    }

    temp = *(str + left_iter);
    *(str + left_iter) = *(str - left_iter);
 }
/*************************************************************/

char* Reverse (char *str)
{
    return Reverse_helper(str, 0, Strlen(str)-1);
}


char* Reverse_helper (char *str, size_t inx_r, size_t inx_l)
{
    if (inx_r >= inx_l)
    {
        return str;
    }

    Swap(str+inx_r, str+inx_l);
    return Reverse_helper(str, ++inx_r, --inx_l);
}


void Swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
