#include <stddef.h> /* 	  size_t 	 */
#include <assert.h> /* 	  assert	 */
#include <stdlib.h> /* malloc, free */

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

/*------------- DLL Iterator Functionality -------------*/
dll_iter_t DLLBegin(const dll_t *target_dll)
{
	dll_iter_t begin_iter;
	begin_iter.current = target_dll->start;
	
	return begin_iter;
}

dll_iter_t DLLEnd(const dll_t *target_dll);
{
	dll_iter_t end_iter;
	end_iter.current = target_dll->end;
	
	return end_iter;
}

dll_iter_t DLLIterNext(dll_iter_t cur_iter)
{
	dll_iter_t next_iter;
	next_iter.current = cur_iter->next;
	
	return next_iter;
}

dll_iter_t DLLIterPrev(dll_iter_t cur_iter)
{
	dll_iter_t prev_iter;
	prev_iter.current = cur_iter->prev;
	
	return prev_iter;
}

int DLLIterIsEqual(dll_iter_t iter_1, dll_iter_t iter_2)
{
	return (iter_1 == iter_2);
}

void *DLLIterGetData(dll_iter cur_iter)
{
	return cur_iter.current->data;
}
/*------------------------------------------------------*/


