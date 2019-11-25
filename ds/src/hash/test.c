#include <stddef.h> /*	size_t	        */
#include <stdlib.h> /*	malloc, free	*/
#include <assert.h> /*  assert          */

#include "dll.h"    /* dll API     */
#include "hash.h"   /* hash API    */


/* ############################### Struct Definitions & Typedefs ################################ */
struct hash
{
    hash_func_t hash_func;
    hash_cmp_func_t cmp_func;
    size_t capacity;
    dll_t *table[1];
};


/* ############################## Internal Functions Declarations ############################### */
static int HASHInitDLL(dll_t **table, size_t table_size);
size_t HASHGetTableIndex(const hash_t *hash, const void *data);
static int HASHSizeHelper(void *data, void *size);

/* ################################## API Function Definitions ################################## */
hash_t *HASHCreate(hash_func_t hash_func, hash_cmp_func_t cmp_func, size_t table_size)
{
    hash_t *new_hash = NULL;

    new_hash = (hash_t*)malloc(offsetof(hash_t, table) + sizeof(new_hash->table) * table_size);
    if (NULL == new_hash)
    {
        return NULL;
    }

    if (1 == HASHInitDLL(new_hash->table, table_size))
    {
        free(new_hash);
        new_hash = NULL;

        return NULL;
    }

    new_hash->hash_func = hash_func;
    new_hash->cmp_func = cmp_func;
    new_hash->capacity = table_size;

    return new_hash;
} 

int HASHInsert(hash_t *hash, const void* data)
{
    size_t index = 0;

    assert(NULL != hash);

    index = HASHGetTableIndex(hash, data);

    if (DLLIterIsEqual(DLLEnd(hash->table[index]), DLLPushFront(hash->table[index], data)))
    {
        return 1;
    }

    return 0;
}

void HASHRemove(hash_t *hash, const void *data)
{
    size_t index = 0; 
    dll_iter_t iter_remove = {NULL};

    assert(NULL != hash);

    index = HASHGetTableIndex(hash, data);

    iter_remove = DLLFind(DLLBegin(hash->table[index]), DLLEnd(hash->table[index]),
                               hash->cmp_func, (void*)data);

    if (! DLLIterIsEqual(DLLEnd(hash->table[index]), iter_remove))
    {
        DLLRemove(iter_remove);
    }
}

size_t HASHSize(const hash_t *hash)
{
    size_t size = 0;

    assert(NULL != hash);

    HASHForEach((hash_t*)hash, &HASHSizeHelper, &size);

    return size;
}

int HASHIsEmpty(const hash_t *hash)
{
    size_t index;
    int is_empty = 1;

    assert(NULL != hash);

    for (index = 0; 1 == is_empty && hash->capacity > index; index++)
    {
        is_empty = DLLIsEmpty(hash->table[index]);
    }
    
    return is_empty;
}

void *HASHFind(const hash_t *hash, const void *data)
{
    size_t index = 0;
    dll_iter_t iter_find = {NULL};

    index = HASHGetTableIndex(hash, data);

    iter_find = DLLFind(DLLBegin(hash->table[index]), DLLEnd(hash->table[index]), hash->cmp_func,
                        (void*)data);
    
    if (DLLIterIsEqual(DLLEnd(hash->table[index]), iter_find))
    {
        return NULL;
    }

    return DLLIterGetData(iter_find);
}

int HASHForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
    size_t index = 0;
    int is_success = 0;

    assert(NULL != hash);

    for (index = 0; 0 == is_success && hash->capacity > index; index++)
    {
        is_success = DLLForEach(DLLBegin(hash->table[index]), DLLEnd(hash->table[index]),
                                action_func, param);
    }

    return is_success;
}

void HASHDestroy(hash_t *hash)
{
    size_t index = 0;

    for(index = 0; hash->capacity > index; index++)
    {
        DLLDestroy(hash->table[index]);
        hash->table[index] = NULL;
    }

    free(hash);
    hash = NULL;
}


/* ########################### Internal Utility Functions Definitions ############################ */
static int HASHInitDLL(dll_t **table, size_t table_size)
{
    size_t i = 0;

    for (i = 0; table_size > i; i++)
    {
        table[i] = DLLCreate();
        if (NULL == table[i])
        {
            for (; 0 <= i; i--)
            {
                free(table[i]);
                table[i] = NULL;
            }

            return 1;
        }
    }

    return 0;
}





static int HASHSizeHelper(void *data, void *size)
{
    (void) data;
    (*(size_t*)size)++;

    return 0;
}