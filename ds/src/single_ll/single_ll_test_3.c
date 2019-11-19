#include <stdio.h>  /*printf*/
#include <stdlib.h> /*free*/

#include "single_ll.h"  

#define SET_RED_COLOR "\033[0;31m"  
#define SET_BLUE_COLOR "\033[0;34m"
#define SET_CYAN_COLOR "\033[0;36m"
#define RESET_COLOR "\033[0m"


/******************************************************************************/
/*             			Internal Component Declaration         				  */
/******************************************************************************/
static int arr[10] = {0};

int AddNum(void *data, void *num);
int Find(const void* data, void* cmp);
void PrintSingleLinkedList(sll_node_t *node);
/******************************************************************************/

/******************************************************************************/
/*                         Test Functions Declaration                         */
/******************************************************************************/
void SingleLinkedListTest();
/******************************************************************************/



/******************************************************************************/
/*                         Test Functions Definition                          */
/******************************************************************************/
void SingleLinkedListTest()
{
	int i = 0;
	sll_node_t *node = NULL;
	sll_node_t *root = NULL;	
	sll_node_t *temp = NULL;
	
	sll_node_t *intersection= NULL;
	sll_node_t *find= NULL;
	
	sll_node_t *nodeA = NULL;
	sll_node_t *nodeB = NULL;
	sll_node_t *nodeC = NULL;

	int a = 1;
	int b = 2;
	int c = 3;
	
	int param = 2;
	int nocmp = 6;
	int cmp = 4;

	/* Create & Insert Test */
	printf("\n\t%sCreating Nodes and performing Insert%s\n", SET_RED_COLOR, RESET_COLOR);
	nodeC = SLLCreateNode(&c,NULL);
	nodeB =  SLLCreateNode(&b,nodeC);
	nodeA = SLLCreateNode(&a,nodeB);

	/* init empty arr */
	for(i = 0; i < 10; i++)
	{
		arr[i] = i;
	}

	/* create nodes for each element in array */
	for(i = 0; i < 10; i++)
	{
		root = SLLCreateNode(&arr[i], root);
	}

	node = root;
	/* print the values */
	PrintSingleLinkedList(node);
	
	node = root->next_node;

	/* Remove and RemoveAfter Test */
	printf("\n\t%s Remove and RemoveAfter Test %s\n", SET_RED_COLOR, RESET_COLOR);
	
	/* remove second node */
	SLLRemove(node);
	
	node = root;

	printf("\n\t\t%s Remove second node %s\n", SET_RED_COLOR, RESET_COLOR);

	/* re-print after removing */
	PrintSingleLinkedList(node);

	/* remove second node->next node */
	printf("\n\t\t%s Remove second node -> next node %s\n", SET_RED_COLOR, RESET_COLOR);

	node = root->next_node;
	SLLRemoveAfter(node);
	node = root;

	PrintSingleLinkedList(node);

	/* Insert and InsertAfter test */ 
	printf("\n\t%s Insert and InsertAfter Test %s\n", SET_RED_COLOR, RESET_COLOR);

	/* inserting node to 3rd node */
	printf("\n\t\t%s Inserting node to 3rd node %s\n", SET_RED_COLOR, RESET_COLOR);

	node = SLLCreateNode(&b, NULL);
	temp = (root->next_node)->next_node;
	SLLInsert(temp, node);
	node = root;

	PrintSingleLinkedList(node);

	/* inserting node to 3rd node -> next node */
	printf("\n\t\t%s Inserting node to 3rd node ->next node %s\n", SET_RED_COLOR, RESET_COLOR);

	node = SLLCreateNode(&c, NULL);
	temp = (root->next_node)->next_node;
	SLLInsertAfter(temp, node);
	node = root;

	PrintSingleLinkedList(node);

	/* Count Test */
	printf("\n\t%s Count Test %s\n", SET_RED_COLOR, RESET_COLOR);

	if (SLLCount(root) == 10)
	{
		printf ("success\n");
	}
	else 
	{
		printf ("failure\n");
	}	

	/* Find Test */
	printf("\n\t%s Find Test %s\n", SET_RED_COLOR, RESET_COLOR);

	find = SLLFind(root, &Find, &nocmp);

	if (find == NULL)
	{
		printf("success\n");
	}
	else 
	{
		printf ("failure\n");
	}
	
	find = SLLFind(root, &Find, &cmp);

	if (*(int*)find->data == 4)
	{
		printf("success\n");
	}
	else 
	{
		printf ("failure\n");
	}

	/* Intersection Test */
	printf("\n\t%s Intersection Test %s\n", SET_RED_COLOR, RESET_COLOR);

	intersection= SLLFindIntersection(root, nodeA);
	if (intersection == NULL)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
		
	nodeB->next_node = root;
	
	intersection = SLLFindIntersection(root, nodeA);
	if (*(int*)intersection->data == 9)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	

	/* HasLoop test */
	printf("\n\t%s HasLoop Test %s\n", SET_RED_COLOR, RESET_COLOR);

	if (SLLHasLoop(root) == 0)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	nodeB->next_node = nodeC;
	nodeC->next_node = nodeA;
	
	if (SLLHasLoop(nodeA) == 1)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}

	/* ForEach test */
	printf("\n\t%s ForEach Test %s\n", SET_RED_COLOR, RESET_COLOR);

	SLLForEach(root, &AddNum, &param);	
	printf("values after adding 2 to each one: \n");
	
	node = root;
	
	PrintSingleLinkedList(node);

	/* Flip Test */
	printf("\n\t%s Flip Test %s\n", SET_RED_COLOR, RESET_COLOR);
	
	node = SLLRecFlip(root);

	printf("\nafter fliping:\n"); 

	PrintSingleLinkedList(node);
	
	SLLFreeAll(root);
	
	nodeC->next_node = NULL;
	SLLFreeAll(nodeA);
}
/******************************************************************************/

int main()
{
		
	SingleLinkedListTest();
	
	return 0;
}

/******************************************************************************/
/*             			Internal Component Definition         				  */
/******************************************************************************/
int AddNum(void *data, void *num)
{
	*(int *)data += *(int *)num;
	return 0;
} 

int Find(const void* data, void* cmp)
{
	if (*(int *)data == *(int *)cmp)
	{
		return 0;
	}
	
	return 1;
}

void PrintSingleLinkedList(sll_node_t *node)
{
	printf("\n");
	while(NULL != node)
	{
		printf("%s %d%s", SET_BLUE_COLOR, *((int *)node->data), RESET_COLOR);
		node = node->next_node;
	}	
	printf("\n");
}
/******************************************************************************/





