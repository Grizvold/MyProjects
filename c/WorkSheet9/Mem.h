#ifndef __MEM_H__
#define __MEM_H__
#include <stddef.h> /* size_t */

/* fills first n bytes of the memory area pointed to by s with byte c */
extern void *MemSet(void *source, int c, size_t n);

/* copy n bytes from source to dest */
extern void *MemCpy(void *dest, const void *src, size_t n);
#endif
