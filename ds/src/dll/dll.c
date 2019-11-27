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
	
	new_dll = (dll_t *)malloc(sizeof(*new_dll));
	if(NULL == new_dll)
	{
		perror("malloc in DLLCreate failed");
		
		return NULL;
	}

	/* head and tail are part of struct */
	new_dll->tail.prev = &new_dll->head;
	new_dll->tail.next = NULL;

	new_dll->head.next = &new_dll->tail;
	new_dll->head.prev = NULL;
	
	return new_dll;
}

void DLLDestroy(dll_t *target_dll)
{
	/* dll_node_t *temp_node = NULL;*/
	
	assert(NULL != target_dll);
	
	for(; !DLLIsEmpty(target_dll);)
	{
		DLLPopFront(target_dll);
	}
	
	free(target_dll);
}

int DLLIsEmpty(const dll_t *target_list)
{
	assert(NULL != target_list);

	return target_list->head.next == &target_list->tail;
}

dll_iter_t DLLInsert(dll_iter_t dll_iterator, const void *data)
{
	dll_node_t *new_node = NULL;
	dll_iter_t new_iterator = {NULL, NULL};
	
	new_node = (dll_node_t *)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{
		perror("Malloc in DLLInsert failed");
		
		return DLLEnd(dll_iterator.cur_list);
	}
	
	new_node->next = dll_iterator.cur_node; 
	new_node->prev = dll_iterator.cur_node->prev;
	new_node->data = (void *)data;
	
	dll_iterator.cur_node->prev->next = new_node;
	dll_iterator.cur_node->prev = new_node;
	
	new_iterator.cur_node = new_node;
	new_iterator.cur_list = dll_iterator.cur_list;	

	return new_iterator;
}

dll_iter_t DLLRemove(dll_iter_t dll_iterator)
{
	dll_node_t *temp_node = NULL;
	dll_iter_t temp_iter = DLLIterNext(dll_iterator);
	
	temp_node = dll_iterator.cur_node;
	
	dll_iterator.cur_node->prev->next = dll_iterator.cur_node->next;
	dll_iterator.cur_node->next->prev = dll_iterator.cur_node->prev;
	

	free(temp_node);
	
	return temp_iter;
}

dll_iter_t DLLPushFront(dll_t *dll_list, const void *data)
{
	assert(NULL != dll_list);
	
	return DLLInsert(DLLBegin(dll_list), (void *)data);
}

void *DLLPopFront(dll_t *dll_list)
{
	void *temp_data = NULL;
	
	assert(NULL != dll_list);
	
	temp_data = DLLBegin(dll_list).cur_node->data;
	
	DLLRemove(DLLBegin(dll_list));
	
	return temp_data;
}

dll_iter_t DLLPushBack(dll_t *dll_list, const void *data)
{
	assert(NULL != dll_list);
	
	return DLLInsert(DLLEnd(dll_list), (void *)data);
}

void *DLLPopBack(dll_t *dll_list)
{
	void *temp_data = NULL;
	
	assert(NULL != dll_list);

	temp_data = DLLIterPrev(DLLEnd(dll_list)).cur_node->data;
	
	DLLRemove(DLLIterPrev(DLLEnd(dll_list)));

	return temp_data;
}

dll_iter_t DLLFind(dll_iter_t start_itr, dll_iter_t end_itr, dll_cmp_func_t cmp_func, void *param)
{
	for(; !DLLIterIsEqual(start_itr, end_itr); start_itr = DLLIterNext(start_itr))
	{
		if(1 == cmp_func(DLLIterGetData(start_itr), param))
		{
			break;
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
	dll_iter_t to_prev = DLLIterPrev(to);
	
	/* disconect <from>-<to> from previous dll and rechain */
	from.cur_node->prev->next = to.cur_node;
	to.cur_node->prev = from.cur_node->prev;
	
	/* chain <from>-<to> to <where> dll list   */
	where.cur_node->prev->next = from.cur_node;
	from.cur_node->prev = where.cur_node->prev;
	
	where.cur_node->prev = to_prev.cur_node;
	to_prev.cur_node->next = where.cur_node;
	
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
	end_iter.cur_node = &(((dll_t *)target_dll)->tail);
	
	return end_iter;
}

dll_iter_t DLLIterNext(dll_iter_t cur_iter)
{
	dll_iter_t next_iter = {NULL, NULL};

	assert(NULL != cur_iter.cur_list);
	
	next_iter.cur_node = cur_iter.cur_node->next;
	next_iter.cur_list = cur_iter.cur_list;
	
	return next_iter;
}

dll_iter_t DLLIterPrev(dll_iter_t cur_iter)
{
	dll_iter_t prev_iter = {NULL, NULL};

	assert(NULL != cur_iter.cur_list);
	
	prev_iter.cur_node = cur_iter.cur_node->prev;
	prev_iter.cur_list = cur_iter.cur_list;
	
	return prev_iter;
}

int DLLIterIsEqual(dll_iter_t iter_1, dll_iter_t iter_2)
{
	assert(NULL != iter_1.cur_list && NULL != iter_2.cur_list);

	return ((iter_1.cur_list == iter_2.cur_list) && 
			(iter_1.cur_node == iter_2.cur_node));
}

void *DLLIterGetData(dll_iter_t cur_iter)
{
	if(DLLIterIsEqual(cur_iter, DLLEnd(cur_iter.cur_list)))
	{
		
		return NULL;
	}

	return cur_iter.cur_node->data;
}
/*------------------------------------------------------*/


