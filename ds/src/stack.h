#ifndef __stack_h__
#define __stack_h__

#include <stddef.h>

typedef struct stack stack_t;

stack_t *StkCreate(size_t size);

void StkPush(stack_t *element, void *item);

void *StkPop(stack_t *element);

void *StkPeek(const stack_t *element);

size_t StkCount(const stack_t *element);

int StkIsEmpty(const stack_t *element);

void StkDestroy(stack_t *element);


#endif /* stack */
