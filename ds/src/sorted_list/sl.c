#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc,free */
#include <assert.h> /* assert */
#include <stdio.h> /* perror */

#include "sl.h"
#include "dll.h"

struct sl
{
	dll_t *list;
	sl_is_before_t IsBefore;
	void *param;
};

/*################## Sorted List Functionality ###################*/

sl_t *SLCreate(sl_is_before_t is_before_func, void *param)
{
	sl_t *new_sl = NULL;

	new_sl = (sl_t*)malloc(sizeof(*new_sl));
	if (NULL == new_sl)
	{
		perror("SLCreate malloc failed");

		return NULL;
	}

	new_sl->list = DLLCreate();
	if(NULL == new_sl->list)
	{
		perror("SLCreate - DLLCreate malloc failed");
		free(new_sl);

		return NULL;		
	}

	new_sl->IsBefore =  is_before_func;
	new_sl->param = param;

	return new_sl;
}

void SLDestroy(sl_t *sl)
{
	assert(NULL != sl);

	DLLDestroy(sl->list);
	free(sl);
}

sl_iter_t SLInsert(sl_t *sl, const void *data)
{
	sl_iter_t sl_iter = {NULL};

	assert(NULL != sl);
	
	for(sl_iter = SLBegin(sl);
		!SLIterIsEqual(sl_iter, SLEnd(sl));
		sl_iter = SLIterNext(sl_iter))
	{
		if(sl->IsBefore((void *)data, SLIterGetData(sl_iter), sl->param))
		{		
			break;
		}
	}

	sl_iter.iter = DLLInsert(sl_iter.iter, (void *)data);

	return sl_iter;
}

sl_iter_t SLRemove(sl_iter_t target_itr)
{
	target_itr.iter = DLLRemove(target_itr.iter);

	return target_itr;
}

void *SLPopBack(sl_t *sl)
{
	assert(NULL != sl);

	return DLLPopBack(sl->list);
}

void *SLPopFront(sl_t *sl)
{
	assert(NULL != sl);

	return DLLPopFront(sl->list);
}

size_t SLSize(const sl_t *target_sl)
{
	assert(NULL != target_sl);

	return DLLSize(target_sl->list);
}

int SLIsEmpty(const sl_t *target_sl)
{
	assert(NULL != target_sl);

	return DLLIsEmpty(target_sl->list);
} 

sl_iter_t SLBegin(const sl_t *target_sl)
{
	sl_iter_t begin_iter = {NULL};

	assert(NULL != target_sl);

	begin_iter.sl = (sl_t *)target_sl;
	begin_iter.iter = DLLBegin(target_sl->list);

	return begin_iter;
}

sl_iter_t SLEnd(const sl_t *target_sl)
{
	sl_iter_t end_iter = {NULL};

	assert(NULL != target_sl);

	end_iter.sl = (sl_t *)target_sl;
	end_iter.iter = DLLEnd(target_sl->list);

	return end_iter;
}

int SLForEach(sl_iter_t from, sl_iter_t to, sl_act_func_t func, void *param)
{
	return DLLForEach(from.iter, to.iter, func, param);
}

sl_iter_t SLFindIf(sl_iter_t from, sl_iter_t to, sl_cmp_func_t func, void *param)
{
	from.iter = DLLFind(from.iter, to.iter, func, param);

	return from;
}

sl_iter_t SLFind(sl_iter_t itr_from, sl_iter_t itr_to, void *data)
{
	sl_t *f_list = itr_from.sl;

	for(;!SLIterIsEqual(itr_from, itr_to); itr_from = SLIterNext(itr_from))
	{
		if(!f_list->IsBefore(data, SLIterGetdata(itr_from), f_list->param))
		{
			break;
		}

		if(!f_list->IsBefore(data, SLIterGetdata(itr_from), f_list->param)
		   && (!f_list->IsBefore(SLIterGetdata(itr_from), data, f_list->param)))
		{
			return itr_from;
		}
	}

	return itr_from;
}

sl_iter_t SLMerge(sl_t *dest, sl_t *src)
{
	sl_iter_t mrg_iter = {NULL};

	for (mrg_iter = SLBegin(dest); 
		!SLIterIsEqual(mrg_iter, SLEnd(dest)) && !SLIsEmpty(src);
		mrg_iter = SLIterNext(mrg_iter))
	{
		if(dest->IsBefore(SLIterGetData(SLBegin(src)), 
					SLIterGetData(mrg_iter), 
					dest->param))
		{
			mrg_iter.iter = DLLSplice(mrg_iter.iter, 
							DLLBegin(src->list), 
							DLLBegin(src->list));			
		}
	}

	if (SLIterIsEqual(mrg_iter, SLEnd(dest)))
	{
		DLLSplice(mrg_iter.iter, 
				DLLBegin(src->list),
				DLLIterPrev(DLLEnd(src->list)));
	}

	return SLBegin(dest);
}
/*################################################################*/

/*############ Sorted List Iterator Functionality ################*/

sl_iter_t SLIterNext(sl_iter_t iter)
{
	sl_iter_t next_iter = {NULL};	

	next_iter.sl = iter.sl;
	next_iter.iter = DLLIterNext(iter.iter);

	return next_iter;
}

sl_iter_t SLIterPrev(sl_iter_t iter)
{
	sl_iter_t prev_iter = {NULL};	

	prev_iter.sl = iter.sl;
	prev_iter.iter = DLLIterPrev(iter.iter);

	return prev_iter;
}

int SLIterIsEqual(sl_iter_t iter1, sl_iter_t iter2)
{
	return (DLLIterIsEqual(iter1.iter, iter2.iter));
}

void *SLIterGetData(sl_iter_t iter)
{
	return DLLIterGetData(iter.iter);
}
/*################################################################*/
