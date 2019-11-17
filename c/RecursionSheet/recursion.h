#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h> /* size_t */

size_t StrLenRec(const char *str);

char *StrCpyRec(char *dest, const char *src);

int StrCmpRec(const char *str1, const char *str2);

char *StrStrRec(const char *haystack, const char *needle);


#endif