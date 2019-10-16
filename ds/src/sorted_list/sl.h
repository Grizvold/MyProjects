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

/*############ Sorted List Iterator Functionality  ###############*/


/*################################################################*/

/*====================== INTERNAL USE ONLY =======================*/

struct sl_iter_t
{
	dll_node_t iter;
	sl_t *sl;
};
/*================================================================*/

#endif /* __SL_H__ */

