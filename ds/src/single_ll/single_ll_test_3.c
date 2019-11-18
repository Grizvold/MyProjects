#include <stdio.h>  /*printf*/
#include <stdlib.h> /*free*/

#include "single_ll.h"  

int AddNum(void *data, void *num);
int Find(const void* data, void* cmp);

int main()
{
	/*for testing create, insert and remove*/
	int arr[10] = {0};
	int i =0;
	sll_node_t *node = NULL;
	sll_node_t *root = NULL;	
	sll_node_t *temp = NULL;
	
	sll_node_t *intersection= NULL;
	sll_node_t *find= NULL;
	
	sll_node_t *nodeA = NULL;
	sll_node_t *nodeB = NULL;
	sll_node_t *nodeC = NULL;
	
	
	int a= 1;
	int b= 2;
	int c= 3;
	
	int param =2;
	int nocmp = 6;
	int cmp =4;
	
	nodeC = SLLCreateNode(&c,NULL);
	nodeB =  SLLCreateNode(&b,nodeC);
	nodeA = SLLCreateNode(&a,nodeB);
	
		printf("\ntesting remove and insert\n");
	
	for(i = 0; i < 10; i++)
	{
		arr[i] = i;
	}

	printf("printing values\n");	
	for(i = 0; i < 10; i++)
	{
		root = SLLCreateNode(&arr[i], root);
	}
	
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next_node;
	}	
		
	node = root->next_node;
	
	printf("\nremoving second node\n");
	SLLRemove(node);
	
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next_node;
	}

	printf("\nremoving second's next_node node\n");
	node = root->next_node;
	SLLRemoveAfter(node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next_node;
	}
	
	printf("\ninserting node to third node\n");
	node = SLLCreateNode(&b, NULL);
	temp = (root->next_node)->next_node;
	SLLInsert(temp, node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next_node;
	}
	
	printf("\ninserting node to third' next_node node\n");
	node = SLLCreateNode(&c, NULL);
	temp = (root->next_node)->next_node;
	SLLInsertAfter(temp, node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next_node;
	}
	
	
	printf ("\ntesting count:\n");
	
	if (SLLCount(root) == 10)
	{
		printf ("success\n");
	}
	else 
	{
		printf ("failure\n");
	}	
		

	printf ("\ntesting Find:\n");
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
	

	
	printf ("\ntesting Intersection:\n");
	/* intersection= SLLFindIntersection(root, nodeA);
	if (intersection == NULL)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
		
	nodeB->next_node = root;
	
	intersection =SLLFindIntersection(root, nodeA);
	if (*(int*)intersection->data == 9)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	} */
	
	printf("\ntesting HasLoop\n");
	
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
	
	printf("\ntesting ForEach\n");	
	SLLForEach(root, &AddNum, &param);	
	printf("values after adding 2 to each one: \n");
	
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next_node;
	}
	
	printf("\n");
	
	node = SLLRecFlip(root);

	printf("\nafter fliping:\n"); 
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next_node;
	}
	
	printf("\n");

	SLLFreeAll(root);
	
	nodeC->next_node = NULL;
	SLLFreeAll(nodeA);
	
	
	return 0;
	
}



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





