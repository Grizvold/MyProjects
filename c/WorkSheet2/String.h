/* string strlen/strcmp/strcpy/strcat implantation */
#ifndef __STRING_H__
#define __STRING_H__
#include <stddef.h> /* size_t */

extern  size_t StrLen(const char *test);

extern int StrCmp(const char *first, const char *second);

extern char *StrCpy(char *dest_string, const char *src_string);
	
extern char *StrCat(char *dest_string, const char *src_string);
#endif
