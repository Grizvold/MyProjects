#ifndef __stack_h__
#define __stack_h__

#include <stddef.h>

typedef struct stack stack_t;

stack_t *StkCreate(size_t size);

void StkPush(stack_t *element, void *item);

void *StkPop(stack_t *element);

void *StkPeek(stack_t *element);

size_t StkCount(stack_t *element);

int StkIsEmpty(stack_t *element);

void StkDestroy(stack_t *element);


#endif /* stack */
