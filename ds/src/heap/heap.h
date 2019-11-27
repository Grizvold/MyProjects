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

/*  -Push to the most left child, and perform Sift-Up.  */
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

size_t HEAPSize(const heap_t *heap);


/******************************************************************************/

#endif /* __HEAP_H__ */
