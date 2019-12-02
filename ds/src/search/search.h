#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stddef.h> /* size_t */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef int (*cmp_func_t)(const void *key1, const void *key2);
/******************************************************************************/

/******************************************************************************/
/*                          Search Functions Declaration                      */
/******************************************************************************/

/*  -Search by repeatedly dividing the search interval in half, using recursion.
    -Time Complexity: O(Log n). 
    -Returns found element. */
void *BinarySearchRec(void *arr,
                      size_t n_members,
                      size_t member_size,
                      void *key,
                      cmp_func_t func);

/*  -Search by repeatedly dividing the search interval in half, using iterator.
    -Time Complexity: O(Log n). 
    -Returns found element. */
void *BinarySearchIter(void *arr,
                       size_t n_members,
                       size_t member_size,
                       void *key,
                       cmp_func_t func);

/*  -Search by jumping ahead by fixed steps(sqrt) or skipping some 
        elements in place of searching all elements.
    -Time Complexity: O(√n).
    -Returns found element. */
void *JumpSearchIter(void *arr,
                     size_t n_members,
                     size_t member_size,
                     void *key,
                     cmp_func_t func);

/******************************************************************************/
#endif /* __SEARCH_H__ */