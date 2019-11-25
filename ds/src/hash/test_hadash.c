#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "hash.h" /* API */
#include "dll.h" /* double link-list */

struct hash
{
    hash_func_t hash_func;
    cmp_func_t cmp_func;
    size_t table_size;
    dll_t* data[1]; /*flexible array */
};


size_t GetIndex(const hash_t *table, const void* data);

/**********************************************************************************/

int HASHInsert(hash_t *table, const void *data)
{
    size_t index = 0;
    
    assert(table && data);
    assert(!HASHFind(table, data));

    index = GetIndex(table, data);

    if (DLLIterIsEqual(DLLEnd(table->data[index]), DLLPushBack(table->data[index], data)))
    {
        return 1;
    }

    return 0;
}


void HASHRemove(hash_t *table, const void* data)
{
    size_t index = 0;

    assert (table && data);

    index = GetIndex(table, data);

    DLLRemove(DLLFind(DLLBegin(table->data[index]), DLLEnd(table->data[index]), table->cmp_func, (void *)data));
}



int HASHIsEmpty(const hash_t *table)
{
    size_t i = 0;

    assert(table);

    for (i = 0; i<table->table_size; ++i)
    {
        if(!DLLIsEmpty(table->data[i]))
        {
            return 0;
        }
    }

    return 1;
}


size_t HASHSize(const hash_t *table)
{
    size_t counter = 0;
    size_t i = 0;

    assert(table);

    for (i = 0; i<table->table_size; ++i)
    {  
        counter += DLLSize(table->data[i]);  
    }

    return counter;

}


void* HASHFind(const hash_t *table, const void *data)
{
    size_t index = 0;

    assert(table && data);

    index = GetIndex(table, data);

    return DLLIterGetData(DLLFind(DLLBegin(table->data[index]), DLLEnd(table->data[index]), table->cmp_func, (void*)data));
    
}


int HASHForEach(hash_t *table, action_func_t func, void *param)
{
    size_t i = 0;
    int status = 0;

    assert(table && func);    

    for (i = 0; i < table->table_size && 0 == status; ++i)
    {
        status = DLLForEach(DLLBegin(table->data[i]), DLLEnd(table->data[i]), func, param);  
    }

    return status;
}


/***********************************************************************************/


