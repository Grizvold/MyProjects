#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stddef.h> /* size_t */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef int(*cmp_func_t)(const void *key1, const void *key2);
/******************************************************************************/

/******************************************************************************/
/*                          Search Functions Declaration                      */
/******************************************************************************/

/*  -Search by repeatedly dividing the search interval in half. 
    -Returns found element. */
void *BinarySearchRec(void *arr, 
                        size_t n_members, 
                        size_t member_size, 
                        void *key, 
                        cmp_func_t func);

/* */
void *BinarySearchIter(void *arr, 
                        size_t n_members, 
                        size_t member_size, 
                        void *key, 
                        cmp_func_t func);

/* */
void *JumpSearchIter(void *arr, 
                        size_t n_members, 
                        size_t member_size, 
                        void *key, 
                        cmp_func_t func);

/******************************************************************************/
#endif /* __SEARCH_H__ */