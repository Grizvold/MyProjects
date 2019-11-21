#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
/*  users's comparison boolean function that returns status:
        0 if not before.
        1 if is before.  */
typedef int (*avl_is_before_t)(const void *data1, const void *data2, void *param);

/*  user's boolean action function that returns status:
        0 for success.
        1 for failure.   */
typedef int (*avl_action_func_t)(void *data, void *param);

typedef struct avl avl_t;
/******************************************************************************/


/******************************************************************************/
/*                          AVL Functions Declaration                         */
/******************************************************************************/
/*  -Creates AVL tree.
    -Returns pointer to created avltree. */
avl_t *AVLCreate(avl_is_before_t func, void *param);
 
 /* -Destroy avl tree by <post-order>. */
void AVLDestroy(avl_t *tree);

/*  -Insert new data to avl tree.
    -boolean function that returns:
        0 for success.
        1 for failure. */
int AVLInsert(avl_t *tree, const void *data);

void AVLRemove(avl_t *tree, const void *data);

/*  -boolean function that returns:
        0 if not empty.
        1 if empty.    */
int AVLIsEmpty(const avl_t *tree);

/*  -Get height of avl tree. */
size_t AVLHeight(const avl_t *tree);

/*  -Returns number of elements in avl tree by <pre-order>.    */
size_t AVLSize(const avl_t *tree);

/*  -Perform action_function on each element in avl tree by <in-order>.
    -Returns status for:
        0 for success.
        1 for failure.  */
int AVLForEach(avl_t *tree, avl_action_func_t func, void *param);

/*  -Find data in avl tree by <binary search>. 
        -Assumption that data exists in tree.   */
void *AVLFind(const avl_t *tree, const void *data);

/*   -Print AVL tree 2D */
void AVLTreePrint(const avl_t *tree);
/******************************************************************************/

#endif /* __AVL_H__ */

