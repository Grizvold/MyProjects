/* string strlen/strcmp/strcpy/strcat implantation */
#ifndef __STRING_H__
#define __STRING_H__
#include <stddef.h> /* size_t */

extern  size_t StrLen(const char *test);

extern int StrCmp(const char *first, const char *second);

extern char *StrCpy(char *dest_string, const char *src_string);
	
extern char *StrCat(char *dest_string, const char *src_string);

extern char *StrDup(const char *src_string);

extern char *StrNCpy(char *dest_string, const char *src_string, size_t n);

extern int StrCaseCmp(const char *s1, const char *);

extern char *StrChr(const char *src, int ch);

extern char *StrNCat(char *dest_string, const char *src_string, size_t n);

extern char *StrStr(const char *hay_stack, const char *needle_);
#endif
