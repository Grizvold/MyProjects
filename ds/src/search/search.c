#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <math.h>   /* sqrt   */

#include "search.h"

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/*                          Internal Functions Declaration                    */
/******************************************************************************/

/* -Returns address of element in <index>.  */
static void *HelperGetItemAddress(void *arr, size_t element_size, size_t index);

/* -Returns middle index. (hight - low) / 2 + low  */
static size_t HelperGetMiddleIndex(size_t low_index, size_t high_index);

static void *BinaryRecursiveSearchHelper(void *array,
                                         size_t element_size,
                                         size_t low_index,
                                         size_t high_index,
                                         void *key,
                                         cmp_func_t func);

static void *BinarySearchIterHelper(void *array,
                                    size_t element_size,
                                    size_t low_index,
                                    size_t high_index,
                                    void *key,
                                    cmp_func_t func);
/******************************************************************************/

/******************************************************************************/
/*                          Search Functions Definition                       */
/******************************************************************************/

void *BinarySearchRec(void *array,
                      size_t n_memb,
                      size_t member_size,
                      void *key,
                      cmp_func_t func)
{
    void *result = NULL;

    assert(NULL != array);
    assert(NULL != key);
    assert(NULL != func);

    /* -Invocation is position = BinRecSearchHelper(value, 0, size - 1) */
    result = BinaryRecursiveSearchHelper(array, 
                                        member_size, 
                                        0, 
                                        n_memb - 1, 
                                        key, 
                                        func);

    return result;
}

void *BinarySearchIter(void *array,
                       size_t n_members,
                       size_t member_size,
                       void *key,
                       cmp_func_t func)
{
    void *result = NULL;

    assert(NULL != array);
    assert(NULL != key);
    assert(NULL != func);

    /* -Invocation is position = BinarySearchIterHelper(value, 0, size - 1) */
    result = BinarySearchIterHelper(array, 
                                    member_size,
                                    0, 
                                    n_members - 1, 
                                    key, 
                                    func);

    return result;
}


void *JumpSearchIter(void *array,
                     size_t n_members,
                     size_t member_size,
                     void *key,
                     cmp_func_t func)
{
    void *return_element = NULL;
    size_t jump_size = 0;
    size_t prev_index = 0;
    int func_result = 0;

    assert(NULL != array);
    assert(NULL != key);
    assert(NULL != func);

    jump_size = sqrt(n_members);


    /* -Find block where element is present(if present at all). */
    for(func_result = func(key, HelperGetItemAddress(array, member_size, jump_size -1)); 
        func_result > 0;
        func_result = func(key, HelperGetItemAddress(array, member_size, jump_size -1)))
    {
        prev_index = jump_size;
        jump_size += sqrt(n_members);
        if(prev_index >= n_members)
        {

            return NULL;
        }
    }

    /* -Do linear search for element in block. Start from <prev_index> */
    for(func_result = func(key, HelperGetItemAddress(array, member_size, prev_index)); 
        func_result > 0;
        func_result = func(key, HelperGetItemAddress(array, member_size, prev_index)))
    {
        prev_index++;
        /* -If we reached end of block or end of <array>. */
        if(n_members == prev_index)
        {

            return NULL;
        }
    }

    /* -If element is found. */
    func_result = func(key, HelperGetItemAddress(array, member_size, prev_index));
    if(0 == func_result)
    {
        return_element = HelperGetItemAddress(array, member_size, prev_index);

        return return_element;
    }

    return NULL;
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Functions Definition                    */
/******************************************************************************/

static void *HelperGetItemAddress(void *arr, size_t element_size, size_t index)
{
    assert(NULL != arr);

    return ((char *)arr + (element_size * index));
}

static size_t HelperGetMiddleIndex(size_t low_index, size_t high_index)
{

    return (high_index - low_index) / 2 + low_index;
}

static void *BinaryRecursiveSearchHelper(void *array,
                                         size_t element_size,
                                         size_t low_index,
                                         size_t high_index,
                                         void *key,
                                         cmp_func_t func)
{
    int func_result = 0;
    size_t mid_index = 0;
    void *mid_element = NULL;
    void *return_element = NULL;

    assert(NULL != array);

    /* -stop condition */
    if (low_index > high_index)
    {

        return NULL;
    }

    /* -compare middle element value to <key> */
    mid_index = HelperGetMiddleIndex(low_index, high_index);
    mid_element = HelperGetItemAddress(array, element_size, mid_index);
    func_result = func(key, mid_element);

    /* -if item present at the middle */
    if (0 == func_result)
    {
        return_element = mid_element;
    }
    /* -element is greater than mid element, 
            hance can be only present in right subarray.    */
    else if (0 < func_result)
    {
        return_element = BinaryRecursiveSearchHelper(array,
                                                     element_size,
                                                     mid_index + 1,
                                                     high_index,
                                                     key,
                                                     func);
    }
    /*  -element is smaller than mid element,
            hance can be only present in left subarray.     */
    else
    {
        return_element = BinaryRecursiveSearchHelper(array,
                                                     element_size,
                                                     low_index,
                                                     mid_index,
                                                     key,
                                                     func);
    }

    return return_element;
}

static void *BinarySearchIterHelper(void *array,
                                    size_t element_size,
                                    size_t low_index,
                                    size_t high_index,
                                    void *key,
                                    cmp_func_t func)
{
    int func_result = 0;
    size_t mid_index = 0;
    void *mid_element = NULL;
    void *return_element = NULL;

    mid_index = HelperGetMiddleIndex(low_index, high_index);
    mid_element = HelperGetItemAddress(array, element_size, mid_index);

    for (;
         low_index <= high_index && NULL == return_element;
         mid_index = HelperGetMiddleIndex(low_index, high_index))
    {
        mid_element = HelperGetItemAddress(array, element_size, mid_index);
        func_result = func(key, mid_element);

        /* -Check if element present at the mid. */
        if (0 == func_result)
        {
            return_element = mid_element;
        }
        /* -Element is greater than mid element, ignore left subarray. */
        else if (0 < func_result)
        {
            low_index = mid_index + 1;
        }
        /* -Element is smaller than mid element, ignore right subarray. */
        else
        {
            high_index = mid_index - 1;
        }
    }

    return return_element;
}
/******************************************************************************/