#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /*  size_t  */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
typedef struct heap heap_t;
/*  -User is_before function.
    -Returns: if data_1 < data_2:
        1 if true.
        0 if false. */
typedef int (*is_before_t)(const void *data_1, const void *data_2, void *param);
typedef int(*is_match_t)(const void *data_1, const void *data_2);
/******************************************************************************/

/******************************************************************************/
/*                          Heap Functions Declaration                        */
/******************************************************************************/
/*  -Creates new HEAP.
    -Returns pointer to created HEAP.
        In case of failure returns NULL.    */
heap_t *HEAPCreate(is_before_t func, void *param);

/*  -Destroys created HEAP. */
void HEAPDestroy(heap_t *heap);

/*  -Push to the most left child, and perform Sift-Up.
    -Returns status:
        0 for success.
        1 for failure.  */
int HEAPPush(heap_t *heap, const void *data);

/*  -Pops up the <root> of the tree, and perform Sift-Down. */
void HEAPPop(heap_t *heap);

/*  -Peeks to the <root> of tree.
    -Returns data.  */
void *HEAPPeek(heap_t *heap);

/*  -Checks if HEAP is empty.
    -Returns:
        1 if empty
        0 if not empty. */
int HEAPIsEmpty(const heap_t *heap);

/*  -Returns number of elements in heap.    */
size_t HEAPSize(const heap_t *heap);

/*  -Find requested data in heap.
    -Returns data of that element. */
void *HEAPFind(heap_t *heap, is_match_t match_func, void *data);

/*  -Removes requested element from heap.   */
void HEAPRemove(heap_t *heap, is_match_t match_func, void *data); 
/******************************************************************************/

#endif /* __HEAP_H__ */
