/*	string strlen/strcmp/strcpy/strcat/strdup/strncpy/	*/
/*	strcasecmp/strchar/strncat/strstr/strncmp/strspn	*/
/*	 implantation						*/
#ifndef __STRING_H__
#define __STRING_H__
#include <stddef.h> /* size_t */

/* Counting string elements untill we reach \0	*/
extern  size_t StrLen(const char *test);

/* run on strings and compare if they differ 								  */ 
extern int StrCmp(const char *first, const char *second);

/* copies the source string to destination string	*/
extern char *StrCpy(char *dest_string, const char *src_string);

/* add the source string to the end of destination string	*/	
extern char *StrCat(char *dest_string, const char *src_string);

/* duplicate a string to a dynamic obtained memory using malloc	*/
extern char *StrDup(const char *src_string);

/* function copies src to the buffer pointed to by dest. most n  bytes  of  src  are copied.	*/
extern char *StrNCpy(char *dest_string, const char *src_string, size_t n);

/* compares 2 strings without sensibility to cases by using xor for letters */
extern int StrCaseCmp(const char *s1, const char *);

/* function returns a pointer to the first occurrence of the character search_char in the string source_string. */
extern char *StrChr(const char *src, int ch);

/* add the [num] number of elemets from source string to the end of destination string	*/
extern char *StrNCat(char *dest_string, const char *src_string, size_t n);

/* function  finds  the first occurrence of the substring needle in the string haystack. */
extern char *StrStr(const char *hay_stack, const char *needle_);

/* run on strings and compare if they differ of second string num bytes of first_string and second_string */ 
extern int StrNCmp(const char *first, const char *second, size_t n);

/* func calc the lenght of the initial substring of string pointed to by first_string	*/ 
extern size_t StrSpn(const char *source_string, const char *accept);

/* function  breaks a string into a sequence of zero or more nonempty tokens.	*/
extern char *StrTok(char *str, const char* delim); 

/* function computes the length of the maximum initial segment	*/
/* of the string pointed to by s1 which consists entirely	*/
/* of characters not from the string pointed to by s2		*/
extern size_t StrCSpn(const char *s1, const char *s2);
#endif
