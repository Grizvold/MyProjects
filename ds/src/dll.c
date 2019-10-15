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

/* list */
struct dll_list
{
	dll_node_t *start;
	dll_node_t *end;
	size_t list_size;
};

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

	new_dll->start = NULL;
	new_dll->end = NULL;

	return new_dll;
}

void DLLDestroy(dll_t *target_dll)
{
	dll_node_t *temp_node = NULL;
	
	assert(NULL != target_dll);
	
	for(temp_node = target_dll->start; NULL != target_dll->start;)
	{
		temp_node = target_dll->start;
		target_dll->start = target_dll->start->next;
		
		free(temp_node);
		temp_node = NULL;
	}
	
	target_dll->end = NULL;
	target_dll->start = NULL;
	
	free(target_dll);
	target_dll = NULL;
}

dll_iter_t DLLInsert(dll_iter_t dll_iterator, const void *data)
{
	
}

dll_iter_t DLLRemove(dll_iter_t dll_iterator)
{

}

dll_iter_t DLLPushFront(dll_iter_t dll_iterator, const void *data)
{
	
}

void *DLLPopFront(dll_iter_t dll_iterator)
{
	
}

dll_iter_t DLLPushBack(dll_iter_t dll_iterator, const void *data)
{
	
}

void *DLLPopBack(dll_iter_t dll_iterator)
{
	
}

dll_iter_t DLLFind(dll_iter_t start, dll_iter_t end, dll_cmp_func_t cmp_func, void *param)
{
	
}

int DLLForEach(dll_iter_t start, dll_iter_t end, dll_act_func_t act_func, void *param)
{
	
}

dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
	
}

size_t DLLSize(const dll_t *target_list)
{
	size_t dll_size = 0;
	dll_iter_t temp_iter = {NULL, NULL};
	
	assert(NULL != target_list);
	
	 
}
/*------------------------------------------------------*/

/*------------- DLL Iterator Functionality -------------*/
dll_iter_t DLLBegin(const dll_t *target_dll)
{
	dll_iter_t begin_iter = {NULL, NULL};
	
	assert(NULL != target_dll);
	
	begin_iter.cur_list = (dll_t *)target_dll;
	begin_iter.cur_node = target_dll->start;
	
	return begin_iter;
}

/* returns EndIterator
   	refering to <past-the-end> element	*/	
dll_iter_t DLLEnd(const dll_t *target_dll);
{
	dll_iter_t end_iter = {NULL, NULL};
	
	assert(NULL != target_dll);
	
	end_iter.cur_list = (dll_t *)target_dll;
	return end_iter;
}

dll_iter_t DLLIterNext(dll_iter_t cur_iter)
{
	dll_iter_t next_iter = {NULL, NULL};
	
	assert(NULL != cur_iter.cur_list);
	
	next_iter.cur_list = cur_iter.cur_list;
	next_iter.cur_node = cur_iter->next;
	
	return next_iter;
}

dll_iter_t DLLIterPrev(dll_iter_t cur_iter)
{
	dll_iter_t prev_iter = {NULL, NULL};
	
	assert(NULL != cur_iter.cur_list);
	
	prev_iter.cur_list = cur_iter.cur_list;
	prev_iter.cur_node = cur_iter->prev;
	
	return prev_iter;
}

int DLLIterIsEqual(dll_iter_t iter_1, dll_iter_t iter_2)
{
	assert(NULL != iter_1.cur_list && NULL != iter_2.cur_list);

	return ((iter_1.cur_list == iter_2_cur_list) && 
			iter_1.cur_node == iter_2_cur_node));
}

void *DLLIterGetData(dll_iter cur_iter)
{
	return cur_iter.cur_node->data;
}
/*------------------------------------------------------*/


