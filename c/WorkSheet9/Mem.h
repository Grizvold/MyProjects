#ifndef __MEM_H__
#define __MEM_H__

#include <stddef.h> /* size_t */

/* fills first n bytes of the memory area pointed to by s with byte c */
void *MemSet(void *source, int c, size_t n);

/* copy n bytes from source to dest */
void *MemCpy(void *dest, const void *src, size_t n);

/* copies n bytes from memory area src to memory area dest	*/
/* memory areas may overlap							*/
void *MemMove(void *dest, const void *src, size_t n);

#endif /* mem */
