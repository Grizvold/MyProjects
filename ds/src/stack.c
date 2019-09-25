#include <stddef.h> /*	   size_t		*/
#include <stdlib.h> /* 	malloc, free 	*/
#include <string.h> /* 	   memcpy		*/

#include "stack.h"

struct stack
{
	int top;
	int max_size;
	void *base_of_data;
	int item_size;
};

stack_t *StkCreate(size_t size_of_stack, size_t element_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	if(NULL == stack)
	{
		/*perror("malloc failed");*/

		return NULL;
	}

	stack->top = 0;
	stack->max_size = size_of_stack;
	stack->base_of_data = calloc(element_size, size_of_stack); /* n, sizeof */
	stack->item_size = element_size;
	if(NULL == stack->base_of_data)
	{
		/*perror("calloc failed");*/

		return NULL;
	}

	return stack;
}

void StkPush(stack_t *p_stack, void *element)
{
	if(p_stack->top == p_stack->max_size)
	{
		return;
	}

	memcpy((char *)p_stack->base_of_data + (p_stack->top * p_stack->item_size),
		 element, p_stack->item_size);
	 
	p_stack->top++;
}

void StkPop(stack_t *p_stack)
{
	if(0 == p_stack->top)
	{
		
		return;
	}

	p_stack->top--;
}

void *StkPeek(const stack_t *p_stack)
{
	return (char *)p_stack->base_of_data + 
				((p_stack->top - 1) * p_stack->item_size);
}

size_t StkCount(const stack_t *p_stack)
{
	return p_stack->top;
}

int StkIsEmpty(const stack_t *p_stack)
{
	return (0 == p_stack->top);
}

void StkDestroy(stack_t *p_stack)
{
	
	free(p_stack->base_of_data);
	p_stack->base_of_data = NULL;
	
	free(p_stack);
	p_stack = NULL;
}
