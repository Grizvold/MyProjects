#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <math.h>   /*  sqrt  */

#include "search.h"   /* search API */


/* ###################################### Typedef & Structs ##################################### */
/* struct for blocks in the jump search */
typedef struct
{
    size_t start;
    size_t end;
} jump_block_t;


/* ############################## Internal Functions Declarations ############################### */
static void *BinarySearchRecHelper(void *arr, size_t member_size, void *key, cmp_func_t func,
                            size_t lo, size_t hi);
static void *SearchBlock(void *arr, size_t member_size, jump_block_t block, void *key,
                         cmp_func_t func);
static jump_block_t GetBlock(size_t start, size_t n_members, size_t block_size);

/* utility functions */
static void *GetItemAddress(void *arr, size_t item_size, size_t index);
static size_t GetMiddleOfRange(size_t lo, size_t hi);


/* ################################## API Functions Definitions ################################# */

/* ********************************************************************************************** */
/*                                    Binary Search - Recursive                                   */
/* ********************************************************************************************** */
void *BinarySearchRec(void *arr, size_t n_members, size_t member_size, void *key, cmp_func_t func)
{
    void *return_data = NULL;

    assert(NULL != arr);
    assert(NULL != key);
    assert(NULL != func);

    return_data = BinarySearchRecHelper(arr, member_size, key, func, 0, n_members - 1);

    return return_data;
}

/***************************** intenal function of BinarySearchRec() ******************************/
static void *BinarySearchRecHelper(void *arr, size_t member_size, void *key, cmp_func_t func,
                            size_t lo_idx, size_t hi_idx)
{
    void *return_data = NULL;
    void *mid_val = NULL;
    size_t mid_idx = 0;
    int cmp_result = 0;

    if (lo_idx > hi_idx)
    {
        return NULL;
    }

    /* getting value of the middle item in the current
        range, and comparing it to the key             */
    mid_idx = GetMiddleOfRange(lo_idx, hi_idx);
    mid_val = GetItemAddress(arr, member_size, mid_idx);
    cmp_result = func(key, mid_val);

    /* deciding what to to do, based on the result of the comparison */
    if (0 == cmp_result)
    {
        return_data =  mid_val;
    }
    else if (0 > cmp_result)
    {
        return_data = BinarySearchRecHelper(arr, member_size, key, func, lo_idx, mid_idx);
    }
    else
    {
        return_data = BinarySearchRecHelper(arr, member_size, key, func, mid_idx + 1, hi_idx);
    }

    return return_data;
}


/* ********************************************************************************************** */
/*                                    Binary Search - Iterative                                   */
/* ********************************************************************************************** */
void *BinarySearchIter(void *arr, size_t n_members, size_t member_size, void *key, cmp_func_t func)
{
    size_t lo_idx = 0, hi_idx = 0, mid_idx = 0;
    void *mid_val = NULL;
    void *search_result = NULL;
    int cmp_result = 0;

    assert(NULL != arr);
    assert(NULL != key);
    assert(NULL != func);

    for (lo_idx = 0, hi_idx = n_members - 1, mid_idx = GetMiddleOfRange(lo_idx, hi_idx);
         lo_idx <= hi_idx && NULL == search_result;
         mid_idx = GetMiddleOfRange(lo_idx, hi_idx))
    {
        /* getting value of the middle item in the current
           range, and comparing it to the key             */
        mid_val = GetItemAddress(arr, member_size, mid_idx);
        cmp_result = func(key, mid_val);

        /* deciding what to to do, based on the result of the comparison */
        if (0 == cmp_result)
        {
            search_result = mid_val;
        }
        else if (0 > cmp_result)
        {
            hi_idx = mid_idx;
        }
        else
        {
            lo_idx = mid_idx + 1;
        }
    }
    
    return search_result;
}


/* ********************************************************************************************** */
/*                                         Jump Search                                            */
/* ********************************************************************************************** */
void *JumpSearchIter(void *arr, size_t n_members, size_t member_size, void *key, cmp_func_t func)
{
    size_t block_size = 0;
    size_t start_of_block = 0;
    jump_block_t block = {0};
    void *search_result = NULL;

    assert(NULL != arr);
    assert(NULL != key);
    assert(NULL != func);

    block_size = sqrt(n_members);

    for (start_of_block = 0;
         start_of_block < n_members && NULL == search_result;
         start_of_block = block.end + 1)
    {
        block = GetBlock(start_of_block, n_members, block_size);
        search_result = SearchBlock(arr, member_size, block, key, func);
    }

    return search_result;
}

/****************************** intenal function of JumpSearchIter() ******************************/
static void *SearchBlock(void *arr, size_t member_size, jump_block_t block, void *key,
                         cmp_func_t func)
{
    size_t i = 0;
    void *curr_item = NULL;
    void *search_result = NULL;
    int cmp_result = 0;

    for (i = block.start; i <= block.end && NULL == search_result; i++)
    {
        curr_item = GetItemAddress(arr, member_size, i);
        cmp_result = func(key, curr_item);
        search_result = (0 == cmp_result) ? curr_item : NULL;
    }

    return search_result;
}

/****************************** intenal function of JumpSearchIter() ******************************/
static jump_block_t GetBlock(size_t start, size_t n_members, size_t block_size)
{
    jump_block_t block = {0};

    block.start = start;
    block.end = start + block_size - 1; /* [--) rule */

    /* this calculation reduces <block.end> to (<n_members> - 1) if it's bigger 
       than that, but doesn't affect <block.end> in any other case.              */
    block.end = block.end - (block.end - block.end % n_members); 

    return block;
}


/* ############################### Utility Functions Definitions ################################ */
static size_t GetMiddleOfRange(size_t lo_idx, size_t hi_idx)
{
    size_t mid_idx = 0;

    mid_idx = lo_idx + (hi_idx - lo_idx) / 2;

    return mid_idx;
}

static void *GetItemAddress(void *arr, size_t item_size, size_t index)
{
    return ((char*)arr + item_size * index);
}