#ifndef __SL_H__
#define __SL_H__

#include <stddef.h> /* size_t */

#include "dll.h" 

/*########################### typedefs ###########################*/

typedef struct sl sl_t;

typedef struct sl_iterator sl_iter_t;

typedef int(*sl_is_before_t)(void *data1, void *data2, void *param);

typedef int(*sl_act_func_t)(void *data, void *param);

typedef int(*sl_cmp_func_t)(const void *data, void *param); 

/*################################################################*/

/*################## Sorted List Functionality ###################*/

sl_t 
/*################################################################*/

/*############ Sorted List Iterator Functionality ################*/

sl_iter_t SLIterNext(sl_iter_t iter);

sl_iter_t SLIterPrev(sl_iter_t iter);

int SLIterIsEqual(sl_iter_t iter1, sl_iter_t iter2);

void *SLIterGetData(sl_iter_t iter);
/*################################################################*/

/*====================== INTERNAL USE ONLY =======================*/

struct sl_iter_t
{
	dll_node_t iter;
	sl_t *sl;
};
/*================================================================*/

#endif /* __SL_H__ */

