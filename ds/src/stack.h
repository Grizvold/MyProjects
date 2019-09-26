#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/*	creates a stack of <size> members by receiving number
   	size_of_stack that will represent amount of members 
   	in stack, and element_size that will represent size 
	of element stored in each stack member.				*/
stack_t *StkCreate(size_t size_of_stack, size_t element_size);

/*	removes the most recently added element, referred 
	to as the top of the stack			 			*/
void StkPop(stack_t *element);

/* 	adds an element to the stack, when stack is 
	full the behavior is undefined 					*/
void StkPush(stack_t *stack, void *element);

/* 	peeks to the top of the stack, but does not remove it 
	form the stack. When stack empty its undefined		*/
void *StkPeek(const stack_t *element);

/* 			count amount of members in the stack	 	*/
size_t StkCount(const stack_t *element);

/* 		boolean function, returns 1 if empty, 0 if not	*/
int StkIsEmpty(const stack_t *element);

/* 				destroys the created stack			*/
void StkDestroy(stack_t *element);

#endif /* __STACK_H__ */
