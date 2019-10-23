#include <stdlib.h> /*	malloc	*/ 
#include <stdio.h>  /*  	perror	*/
#include <assert.h> /*  	assert	*/

#include "single_ll.h"

static int CountHelper(void *data, void *param);
static sll_node_t *GetIntersectionNode(size_t diff, sll_node_t *list1, sll_node_t *list2);

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *node = NULL;
	node = (sll_node_t *)malloc(sizeof(node));
	if (NULL == node)
	{
		perror("Malloc failed in root creation");
		
		return NULL;
	}

	node->data = data;
	node-> next = next;

	return node; 
}

void SLLFreeAll(sll_node_t *target_node)
{
	sll_node_t *temp_node = NULL;
	
	assert(NULL != target_node);
	
	for (temp_node = target_node; 
		NULL != target_node; 
		temp_node = target_node)
	{
		target_node = target_node->next;
		free(temp_node);
	}
	
	free(target_node);
}

sll_node_t *SLLRemove(sll_node_t *target_node)
{
	sll_node_t *temp_node = target_node->next;
	
	assert(NULL != target_node);
	
	target_node->data = temp_node->data;
	target_node->next = temp_node->next;

	free(temp_node);

	return target_node;	
}

sll_node_t *SLLRemoveAfter(sll_node_t *target_node)
{
	sll_node_t *temp_node = NULL;
	
	assert(NULL != target_node);
	
	temp_node = target_node->next;
	target_node->next = temp_node->next;

	free(temp_node);

	return target_node;
}

sll_node_t *SLLInsert(sll_node_t *target_node, sll_node_t *new_node)
{
	void *temp_node_data = new_node->data;
	
	assert(NULL != target_node && NULL != new_node);
	
	SLLInsertAfter(target_node, new_node);
	
	temp_node_data = target_node->data;
	target_node->data = new_node->data;
	new_node->data = temp_node_data;
	
	return new_node;
}

sll_node_t *SLLInsertAfter(sll_node_t *target_node, sll_node_t *new_node)
{
	assert(NULL != target_node && NULL != new_node);
	
	new_node->next = target_node->next;
	target_node->next = new_node;
	
	return target_node;	
}

size_t SLLCount(const sll_node_t *target_node)
{
	size_t node_counter = 0;

	SLLForEach((sll_node_t*)target_node, &CountHelper, &node_counter);
	
	return node_counter;
}

static int CountHelper(void *data, void *param)
{
	UNUSED(data);
	(*(size_t *)param)++;
	
	return 0;
}

int SLLForEach(sll_node_t *head, sll_foreach_func_t func, void *func_param)
{
	sll_node_t *itr = NULL;
	int status = 0;
	
	for (itr = head; NULL != itr; itr = itr->next)
	{
		if (0 != func(head->data, func_param))
		{
			status = 1;		
		
			return status;	
		}		
	}
	
	return status;
}

sll_node_t *SLLFind(const sll_node_t *head, sll_find_func_t func, void *func_param)
{
	sll_node_t *itr = NULL;

	for (itr = (sll_node_t *)head; NULL != itr; itr = itr->next)
	{
		if (0 == func(itr->data, func_param))
		{
			return (sll_node_t *)itr;
		}	
	}
	
	return NULL;
}

sll_node_t *SLLFlip(sll_node_t *head)
{
	sll_node_t *current = NULL;
	sll_node_t *next = NULL;
	sll_node_t *prev = NULL;
	
	assert(NULL != head);
	
	for(current = head; NULL != current;)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	
	head = prev;
	
	return prev;
}

/* returns 1 if there is a loop, 0 if not */
int SLLHasLoop(const sll_node_t *node)
{
	sll_node_t *slow_p = (sll_node_t *)node;
	sll_node_t *fast_p = (sll_node_t *)node;

	/* Floyd's Cycle detection algorithm */ 
	for (; NULL != slow_p && NULL != fast_p && NULL != fast_p->next;
		slow_p = slow_p->next, fast_p = fast_p->next->next)
	{
		/* if slow_p and fast_p meet at some pooint
		   then there is a loop			    		*/
		if (slow_p == fast_p)
		{
		
			return 1;
		}	
	}
		
	return 0;
}

static sll_node_t *GetIntersectionNode(size_t diff, sll_node_t *list1, sll_node_t *list2)
{
	size_t i = 0;
	sll_node_t *cur1 = list1;
	sll_node_t *cur2 = list2;
	
	for(i = 0; i < diff; i++)
	{
		if(NULL == cur1)
		{
		
			return NULL;
		}
		
		cur1 = cur1->next;
	}
	
	for(; NULL != cur1 && NULL != cur2;)
	{
		if(cur1 == cur2)
		{
		
			return cur1->data;
		}
		
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	
	return NULL;
}

sll_node_t *SLLFindIntersection(const sll_node_t *first_list, const sll_node_t *second_list)
{
	size_t len_firtlist = 0;
	size_t len_secondlist = 0;
	size_t diff = 0;
	
	len_firtlist = SLLCount(first_list);
	len_secondlist = SLLCount(second_list);
	
	if(len_firtlist > len_secondlist)
	{
		diff = len_firtlist - len_secondlist;
		
		return GetIntersectionNode(diff, (sll_node_t *)first_list, (sll_node_t *)second_list);
	}
	
	else
	{
		diff = len_secondlist - len_firtlist;
		
		return GetIntersectionNode(diff, (sll_node_t *)second_list, (sll_node_t *)first_list);
	}
	
	

	return NULL;
}


















