#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

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

/* -Returns middle index.   */
static size_t HelperGetMiddleIndex(size_t low_index, size_t high_index);  

static void *BinaryRecursiveSearchHelper(void *array, 
                                size_t element_size, 
                                size_t low_index,
                                size_t high_index,
                                void *key,
                                cmp_func_t func);
/******************************************************************************/


/******************************************************************************/
/*                          Search Functions Definition                       */
/******************************************************************************/

void *BinaryRecursiveSearch(void *array, 
                            size_t n_memb, 
                            size_t memb_size, 
                            void *key,
                            cmp_func_t func)
{
    void *result = NULL;

    assert(NULL != array);
    assert(NULL != key);
    assert(NULL != func);
    
    /* -Invocation is position = BinRecSearchHelper(value, 0, size - 1) */
    result = BinaryRecursiveSearchHelper(array, memb_size, 0, n_memb - 1, key, func);

    return result;
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

    return (low_index + high_index) / 2;
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
    if(high_index > low_index)
    {
        
        return NULL;
    }

    /* -compare middle element value to <key> */
    mid_index = HelperGetMiddleIndex(low_index, high_index);
    mid_element = HelperGetItemAddress(array, element_size, mid_index);
    func_result = func(mid_element, key);
 
    /* -if item found */
    if(0 == func_result)
    {
        return_element = mid_element;
    }
    /* -item is greater than element at location.  */
    else if (0 < func_result)
    {
        return_element = BinaryRecursiveSearchHelper(array, 
                                                    element_size,
                                                    mid_index + 1,
                                                    high_index,
                                                    key,
                                                    func);    
    }
    /*  -item is less than element at location. */
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

/******************************************************************************/
