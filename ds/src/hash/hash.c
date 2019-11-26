#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */
#include <stdio.h>  /* perror       */

#include "dll.h"  /* dll API  */
#include "hash.h" /* hash API */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
typedef enum
{
    SUCCESS,
    FAILURE
} status_t;

struct hash
{
    hash_func_t hash_func;
    hash_cmp_func_t cmp_func;
    size_t capacity;
    dll_t *table[1]; /* flexible array */
};
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/
/* -Create DLL for each cell in HASH table key, of size <table_size>. 
   -Returns status:
        0 in case of success.
        1 in case of failure. In case of failure, also free's all created
                                DLL's up untill failure.  */
static int HASHHelperDLLCreate(hash_t *hash_table, size_t table_size);
/*  -Calculate index in hash table of spesific <data>. */
static size_t HASHHelperGetIndex(const hash_t *hash_table, const void *data);
/******************************************************************************/

/******************************************************************************/
/*                          Hash Functions Definition                         */
/******************************************************************************/
hash_t *HASHCreate(hash_func_t hash_func, hash_cmp_func_t cmp_func, size_t table_size)
{
    hash_t *new_hash_table = NULL;

    while (1)
    {
        new_hash_table = (hash_t *)malloc(offsetof(hash_t, table) + 
                                    table_size * sizeof(new_hash_table->table));

        if (NULL == new_hash_table)
        {
            perror("Malloc in hash_table HASHCreate failed");

            break;
        }

        if (FAILURE == HASHHelperDLLCreate(new_hash_table, table_size))
        {
            perror("Malloc DLL creation failed in HASHCreate");

            break;
        }

        new_hash_table->capacity = table_size;
        new_hash_table->hash_func = hash_func;
        new_hash_table->cmp_func = cmp_func;

        return new_hash_table;
    }

    free(new_hash_table);

    return NULL;
}

void HASHDestroy(hash_t *hash_table)
{
    size_t index = 0;

    assert(NULL != hash_table);

    for(index = 0; index < hash_table->capacity; index++)
    {
        if(NULL != hash_table->table[index]) 
        {
            DLLDestroy(hash_table->table[index]);
        }
    }   

    free(hash_table);
}

int HASHInsert(hash_t *hash_table, const void *data)
{
    size_t index = 0;
 
    assert(NULL != hash_table && NULL != data);

    index = HASHHelperGetIndex(hash_table, data);

    if(DLLIterIsEqual(DLLEnd(hash_table->table[index]), DLLPushBack(hash_table->table[index], data)))
    {
        return FAILURE;
    }

    return SUCCESS;
}

void HASHRemove(hash_t *hash_table, const void *data)
{
    size_t index = 0;
    dll_iter_t remove_itr = {NULL};


    assert(NULL != hash_table && NULL != data);

    index = HASHHelperGetIndex(hash_table, data);
    remove_itr = DLLFind(DLLBegin(hash_table->table[index]),
                        DLLEnd(hash_table->table[index]),
                        hash_table->cmp_func,
                        (void *)data);

    DLLRemove(remove_itr);
}

size_t HASHSize(const hash_t *hash_table)
{
    size_t index = 0;
    size_t counter = 0;

    assert(NULL != hash_table);

    for( index = 0; index < hash_table->capacity; index++)
    {
        counter += DLLSize(hash_table->table[index]);
    }

    return counter;
}

int HASHIsEmpty(const hash_t *hash_table)
{
    size_t index = 0;
    status_t is_empty = FAILURE;

    assert(NULL != hash_table);

    for(index = 0; index < hash_table->capacity && FAILURE == is_empty; index++)
    {
        is_empty = DLLIsEmpty(hash_table->table[index]);
    }

    return is_empty;
}

void *HASHFind(const hash_t *hash, const void *data)
{

}

int HASHForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
    
}
/******************************************************************************/


/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/
static int HASHHelperDLLCreate(hash_t *hash_table, size_t table_size)
{
    int index = 0;

    for(index = 0; index < table_size; index++)
    {
        /* creates DLL for each cell */
        hash_table->table[index] = DLLCreate();
        
        /* check for failure, in case of failure free created DLL's */
        if(NULL == hash_table->table[index])
        {
            HASHDestroy(hash_table);

            return FAILURE;
        }
    }

    return SUCCESS;
}

static size_t HASHHelperGetIndex(const hash_t *hash_table, const void *data)
{
    return hash_table->hash_func(data) % hash_table->capacity;
}
/******************************************************************************/
