#include <stddef.h> /* size_t                         	 */
#include <stdlib.h> /* malloc, calloc, realloc, free  	 */
#include <stdio.h>  /* perror                         	 */
#include <assert.h> /* assert                            */

#include "dll_shai.h"    /* declarations of the dll functions */

/* ################################ Typedefs ################################ */
struct dll_node
{
	struct dll_node *prev;
	struct dll_node *next;
	void *data;
};

struct dll 
{
	dll_node_t tail;
	dll_node_t head;
};

/* ########################### Basic Functions ############################## */
dll_t *DLLCreate()
{
	dll_t *new_dll = NULL;
	
	new_dll = (dll_t*)malloc(sizeof(*new_dll));
	if (NULL == new_dll)
	{
		perror("DLLCreate malloc");
		return NULL;
	}

	new_dll->tail.prev = &new_dll->head;
	new_dll->tail.next = NULL;
	new_dll->head.next = &new_dll->tail;
	new_dll->head.prev = NULL;

	return new_dll;
}

void DLLDestroy(dll_t *dll)
{
	assert(NULL != dll);

	for (; !DLLIsEmpty(dll);)
	{
		DLLPopFront(dll);
	}

	free(dll);	
}

dll_iter_t DLLInsert(dll_iter_t index, void *data)
{
	dll_node_t *new_node = NULL;
	dll_iter_t new_iter = {NULL, NULL};
	
	new_node = (dll_node_t*)malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		perror("DLLInsert malloc");
		return DLLEnd(index.dll_list);
	}
	
	new_node->data = data;

	new_node->prev = index.curr->prev;
	index.curr->prev->next = new_node;
	new_node->next = index.curr;
	index.curr->prev = new_node;

	new_iter.dll_list = index.dll_list;
	new_iter.curr = new_node;
	
	return new_iter;
}

dll_iter_t DLLPushBack(dll_t *dll, const void *data)
{
	assert(NULL != dll);

	return DLLInsert(DLLEnd(dll), (void*)data);
}

dll_iter_t DLLPushFront(dll_t *dll, const void *data)
{
	assert(NULL != dll);

	return DLLInsert(DLLBegin(dll), (void*)data);
}

dll_iter_t DLLRemove(dll_iter_t iter)
{
	dll_node_t *temp_node = iter.curr;
	dll_iter_t temp_iter = {NULL, NULL};

	temp_iter = DLLIterPrev(iter);

	iter.curr->prev->next = iter.curr->next;
	iter.curr->next->prev = iter.curr->prev;

	free(temp_node);
	
	return temp_iter;
}

void *DLLPopBack(dll_t *dll)
{
	void *temp_data = NULL;

	assert(NULL != dll);

	temp_data = DLLIterPrev(DLLEnd(dll)).curr->data;
	DLLRemove(DLLIterPrev(DLLEnd(dll)));

	return temp_data;
}

void *DLLPopFront(dll_t *dll)
{
	void *temp_data = NULL;

	assert(NULL != dll);

	temp_data = DLLBegin(dll).curr->data;
	DLLRemove(DLLBegin(dll));

	return temp_data;
}

/* For internal use in DLLSize */
static int CountHelper(void *data, void *param)
{
	(void)data;

	(*(size_t*)param)++;

	return 0;
}

size_t DLLSize(const dll_t *dll)
{
	size_t size = 0;

	assert(NULL != dll);

	DLLForEach(DLLBegin(dll), (DLLEnd(dll)), &CountHelper, &size);
	
	return size;
}

int DLLIsEmpty(const dll_t *dll)
{
	assert(NULL != dll);

	return (DLLIterIsEqual(DLLBegin(dll), DLLEnd(dll)));
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	dll_iter_t iter_begin = {NULL, NULL};

	assert(NULL != dll);
	
	iter_begin.dll_list = (dll_t*)dll;
	iter_begin.curr = ((dll_t*)dll)->head.next;
	
	return iter_begin;
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	dll_iter_t iter_end = {NULL, NULL};

	assert(NULL != dll);
	
	iter_end.dll_list = (dll_t*)dll;
	iter_end.curr = &(((dll_t*)dll)->tail);
	
	return iter_end;
}

/* ########################## Utility Functions ############################# */
int DLLForEach(dll_iter_t iter_from, dll_iter_t iter_to,
			   dll_act_func_t foreach_func, void *param)
{
	int is_succsess = 0;
	
	for (;
		 ! DLLIterIsEqual(iter_from, iter_to) && 0 == is_succsess;
		 iter_from = DLLIterNext(iter_from))
	{
		is_succsess = foreach_func(DLLIterGetData(iter_from), param);
	}

	return is_succsess;
}

dll_iter_t DLLFind(dll_iter_t iter_from, dll_iter_t iter_to,
				   dll_cmp_func_t cmp_func, void *param)
{
	for (;
		 ! DLLIterIsEqual(iter_from, iter_to);
		 iter_from = DLLIterNext(iter_from))
	{
		if (1 == cmp_func(DLLIterGetData(iter_from), param))
		{
			break;
		}
	}

	return iter_from;
}

dll_iter_t DLLSplice(dll_iter_t iter_where, dll_iter_t iter_from,
					 dll_iter_t iter_to)
{
	iter_from.curr->prev->next = iter_to.curr->next;
	iter_to.curr->next->prev = iter_from.curr->prev;

	iter_where.curr->prev->next = iter_from.curr;
	iter_from.curr->prev = iter_where.curr->prev;

	iter_where.curr->prev = iter_to.curr;
	iter_to.curr->next = iter_where.curr;

	return iter_from;
}

/* ########################## Iterator Functions ############################ */
dll_iter_t DLLIterNext(dll_iter_t iter)
{
	dll_iter_t iter_next = {NULL, NULL};

	iter_next.dll_list = iter.dll_list;	
	iter_next.curr = iter.curr->next;
	
	return iter_next;
}

dll_iter_t DLLIterPrev(dll_iter_t iter)
{
	dll_iter_t iter_prev = {NULL, NULL};
	
	iter_prev.dll_list = iter.dll_list;	
	iter_prev.curr = iter.curr->prev;

	return iter_prev;
}

int DLLIterIsEqual(dll_iter_t iter1, dll_iter_t iter2)
{
	return (iter1.curr == iter2.curr);
}

void *DLLIterGetData(dll_iter_t iter)
{
	return iter.curr->data;
}










