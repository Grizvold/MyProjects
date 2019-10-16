#include <stddef.h> /* 	  size_t 	 */
#include <assert.h> /* 	  assert	 */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /*	  perror	 */

#include "dll.h"

/* node */
struct dll_node
{
	struct dll_node *next;
	struct dll_node *prev;
	void *data;
};

/* list with 2 dummies that are part of list */
struct dll_list
{
	dll_node_t head;
	dll_node_t tail;
};

static int DLLSizeHelper(void *data, void *param);

/*------------------- DLL Funtionality -----------------*/
dll_t *DLLCreate()
{
	dll_t *new_dll = NULL;
	
	new_dll = (dll_t *)malloc(sizeof(new_dll));
	if(NULL == new_dll)
	{
		perror("malloc in DLLCreate failed");
		
		return NULL;
	}

	/* head and tail are part of struct */
	new_dll->head.next = NULL;
	new_dll->head.prev = &new_dll->tail;
	
	new_dll->tail.next = &new_dll->head;
	new_dll->tail.prev = NULL;

	return new_dll;
}

void DLLDestroy(dll_t *target_dll)
{
	dll_node_t *temp_node = NULL;
	
	assert(NULL != target_dll);
	
	for(temp_node = &target_dll->head; temp_node->next != &target_dll->tail;)
	{
		temp_node->next = temp_node->next->next;
		/* free prev(cur) node */
		free(temp_node->next->prev);
		temp_node->next->prev = &target_dll->head;
		target_dll->head.next = temp_node->next;
	}
	
	free(target_dll);
	target_dll = NULL;
}

int DLLIsEmpty(const dll_t *target_list)
{
	assert(NULL != target_list);

	return (target_list->head.next == &target_list->tail);
}

dll_iter_t DLLInsert(dll_iter_t dll_iterator, const void *data)
{
	dll_node_t *new_node = NULL;
	dll_iter_t null_iterator = {NULL, NULL};
	
	new_node = (dll_node_t *)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{
		perror("Malloc in DLLInsert failed");
		
		return null_iterator;
	}
	
	new_node->next = dll_iterator.cur_node; 
	new_node->prev = dll_iterator.cur_node->prev;
	new_node->data = (void *)data;
	
	dll_iterator.cur_node->prev = new_node;
	dll_iterator.cur_node->prev->next = new_node;
	
	dll_iterator.cur_node = new_node;
	
	return dll_iterator;
}

dll_iter_t DLLRemove(dll_iter_t dll_iterator)
{
	dll_iterator.cur_node = dll_iterator.cur_node->next;
	dll_iterator.cur_node->prev = dll_iterator.cur_node->prev->prev;
	free(dll_iterator.cur_node->prev->next);
	dll_iterator.cur_node->prev->next = dll_iterator.cur_node;
	
	return dll_iterator;
}

dll_iter_t DLLPushFront(dll_t *dll_list, const void *data)
{
	dll_node_t *new_node = NULL;
	dll_iter_t push_f_itr = {NULL, NULL};
	
	assert(NULL != dll_list);
	
	
	new_node = (dll_node_t *)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{
		perror("Malloc in DLLPushFront failed");
		
		return DLLEnd(dll_list);
	}
	
	new_node->next = dll_list->head.next;
	new_node->prev = &dll_list->head;
	new_node->data = (void *)data;
	
	dll_list->head.next->prev = new_node;
	dll_list->head.next = new_node;
	
	push_f_itr.cur_node = new_node;
	push_f_itr.cur_list = dll_list;
	
	return push_f_itr;
}

void *DLLPopFront(dll_t *dll_list)
{
	dll_node_t *temp_node = NULL;
	void *temp_data = NULL;
	
	assert(NULL != dll_list);
	
	/* if dll is empty */
	if(dll_list->head.next == &dll_list->tail)
	{
		return NULL;
	}
	
	temp_node = dll_list->head.next;
	temp_data = temp_node->data;

	
	dll_list->head.next = temp_node->next;

	free(dll_list->head.next->prev);
	
	dll_list->head.next->prev = &dll_list->head; 
	
	return temp_data;
}

dll_iter_t DLLPushBack(dll_t *dll_list, const void *data)
{
	dll_node_t *new_node = NULL;
	dll_iter_t push_b_itr = {NULL, NULL};
	
	assert(NULL != dll_list);
	
	
	new_node = (dll_node_t *)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{
		perror("Malloc in DLLPushBack failed");
		
		return DLLEnd(dll_list);
	}
	
	new_node->next = &dll_list->tail;
	new_node->prev = dll_list->tail.prev;
	new_node->data = (void *)data;
	
	dll_list->tail.prev->next = new_node;
	dll_list->tail.prev = new_node;
	
	push_b_itr.cur_node = new_node;
	push_b_itr.cur_list = dll_list;
	
	return push_b_itr;
}

void *DLLPopBack(dll_t *dll_list)
{
	dll_node_t *temp_node = NULL;
	void *temp_data = NULL;
	
	assert(NULL != dll_list);
	
	/* if dll is empty */
	if(dll_list->head.next == &dll_list->tail)
	{
		return NULL;
	}
	
	temp_node = dll_list->tail.prev;
	temp_data = temp_node->data;

	
	dll_list->tail.prev = temp_node->prev;

	free(dll_list->tail.prev->next);
	
	dll_list->tail.prev->next = &dll_list->tail; 
	
	return temp_data;
}

dll_iter_t DLLFind(dll_iter_t start_itr, dll_iter_t end_itr, dll_cmp_func_t cmp_func, void *param)
{
	for(; !DLLIterIsEqual(start_itr, end_itr); start_itr = DLLIterNext(start_itr))
	{
		if(0 == cmp_func(DLLIterGetData(start_itr), param))
		{
			return start_itr;
		}
	}
	
	return start_itr;
}

int DLLForEach(dll_iter_t start_itr, dll_iter_t end_itr, dll_act_func_t act_func, void *param)
{
	int status = 0;
	
	for(; !DLLIterIsEqual(start_itr, end_itr) && 0 == status;
		start_itr = DLLIterNext(start_itr))
	{
		status = act_func(DLLIterGetData(start_itr), param);
	}
	
	return status;
}

dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
	/* disconect <from>-<to> from previous dll */
	from.cur_node->prev->next = to.cur_node->next;
	to.cur_node->next->prev = from.cur_node->prev;
	
	/* chain <from>-<to> to <where> dll list   */
	where.cur_node->prev->next = from.cur_node;
	to.cur_node->next = where.cur_node;
	
	return from;
}


static int DLLSizeHelper(void *data, void *param)
{
	UNUSED(data);
	
	(*(size_t *)param)++;
	
	return 0;
}

size_t DLLSize(const dll_t *target_list)
{
	size_t dll_size = 0;
	
	assert(NULL != target_list);
	
	DLLForEach(DLLBegin(target_list), DLLEnd(target_list), &DLLSizeHelper, &dll_size);
	
	return dll_size;
}
/*------------------------------------------------------*/

/*------------- DLL Iterator Functionality -------------*/
dll_iter_t DLLBegin(const dll_t *target_dll)
{
	dll_iter_t begin_iter = {NULL, NULL};
	
	assert(NULL != target_dll);
	
	begin_iter.cur_list = (dll_t *)target_dll;
	begin_iter.cur_node = target_dll->head.next;
	
	return begin_iter;
}

/* returns EndIterator
   	refering to <past-the-tail> element	*/	
dll_iter_t DLLEnd(const dll_t *target_dll)
{
	dll_iter_t end_iter = {NULL, NULL};
	
	assert(NULL != target_dll);
	
	end_iter.cur_list = (dll_t *)target_dll;
	end_iter.cur_node = target_dll->tail.prev;
	
	return end_iter;
}

dll_iter_t DLLIterNext(dll_iter_t cur_iter)
{
	assert(NULL != cur_iter.cur_list);
	
	cur_iter.cur_node = cur_iter.cur_node->next;
	
	return cur_iter;
}

dll_iter_t DLLIterPrev(dll_iter_t cur_iter)
{
	assert(NULL != cur_iter.cur_list);
	
	cur_iter.cur_node = cur_iter.cur_node->prev;
	
	return cur_iter;
}

int DLLIterIsEqual(dll_iter_t iter_1, dll_iter_t iter_2)
{
	assert(NULL != iter_1.cur_list && NULL != iter_2.cur_list);

	return ((iter_1.cur_list == iter_2.cur_list) && 
			(iter_1.cur_node == iter_2.cur_node));
}

void *DLLIterGetData(dll_iter_t cur_iter)
{
	return cur_iter.cur_node->data;
}
/*------------------------------------------------------*/


