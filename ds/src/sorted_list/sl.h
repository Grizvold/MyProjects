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

/* *Creates new sorted list, where elements will be 
	sorted by is_before function/
   *Returns pointer to the created sl.				 */
sl_t *SLCreate(sl_is_before_t func, void *param);

/* *Destroys selected sorted list					 */
void SLDestroy(sl_t *sl);

/* *Inserts new element to the sorted list
   *Returns iterator				 			 */
sl_iter_t SLInsert(sl_t *sl, const void *data);

/* *Removes element from sorted list				 
   *Returns iterator							 */
sl_iter_t SLRemove(sl_iter_t target_itr);

/* *Removes last element from sorted list
   *Returns data of the last element				 */
void *SLPopBack(sl_t *sl);

/* *Removes first element from sorted list
   *Returns data of the first element				 */
void *SLPopFront(sl_t *sl);

/* *Counts number of elements in sorted list
   *Returns number of counted elements				 */
size_t SLSize(const sl_t *target_sl);

/* *Boolean function that checks if sorted list empty
   *Returns 1 - if empty
   		  0 - if not empty						 */
int SLIsEmpty(const sl_t *target_sl); 

/* *Find element in sorted list
   *Returns iterator to the element				 */
sl_iter_t SLFind(sl_iter_t itr_from, sl_iter_t itr_to, void *data);

/* **/
sl_iter_t SLFindIf(sl_iter_t from, sl_iter_t to, sl_cmp_func_t func, void *param);

/* *Perform action function on each element of the 
	sorted list					
   *Returns status, 1 - in case of failure
    				0 - in case of success			 */
int SLForEach(sl_iter_t from, sl_iter_t to, sl_act_func_t func, void *param);

/* *Receives targeted dll list
   *Returns first element of dl					 */
sl_iter_t SLBegin(const sl_t *target_sl);

/* *Receives targeted dll list
   *Returns iterator refering to 
   	<past-the-end> element in vector container	 	 */
sl_iter_t SLEnd(const sl_t *target_sl);

/* *Merging 2 sorted list into one
   *Returns iterator to new sorted list				 */
sl_iter_t SLMerge(sl_t *dest, sl_t *src);

/*################################################################*/

/*############ Sorted List Iterator Functionality ################*/

sl_iter_t SLIterNext(sl_iter_t iter);

sl_iter_t SLIterPrev(sl_iter_t iter);

int SLIterIsEqual(sl_iter_t iter1, sl_iter_t iter2);

void *SLIterGetData(sl_iter_t iter);
/*################################################################*/

/*====================== INTERNAL USE ONLY =======================*/

struct sl_iterator
{
	dll_iter_t iter;
	sl_t *sl;
};
/*================================================================*/

#endif /* __SL_H__ */

