#include <stdio.h>  /*printf*/

#include "stack.h"


int main ()
{

	struct students
	{
		char* name;
		int class;
	};
	
	struct students student1 = {"hadas", 77};
	struct students student2 = {"yosi", 90};
	
	int empty = 0;
	
	struct students *a = NULL;
	stack_t *my_stack = NULL;
	
	my_stack = StkCreate(3, sizeof(struct students));
	
	empty = StkIsEmpty(my_stack);
	printf("is the stack empty? %d\n" ,empty);
	
	StkPush(my_stack, &student1);
	StkPush(my_stack, &student2);
	
	printf("number of members after pushing: %ld\n" ,StkCount(my_stack));
	
	a = StkPeek(my_stack);
	printf("name of the top student %s\n" ,a->name);
	printf("class of the top student %d\n" ,a->class);
	
	StkPop(my_stack);
	
	printf("number of members: %ld\n" ,StkCount(my_stack));
	
	a = StkPeek(my_stack);
	printf("name of the top student %s\n" ,a->name);
	printf("class of the top student %d\n" ,a->class);
	
	StkDestroy(my_stack);

	empty = StkIsEmpty(my_stack);
	printf("is the stack empty? %d\n" ,empty);

	return 0;
}



