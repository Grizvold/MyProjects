#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h> /* size_t */


/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
typedef struct hash hash_t;

typedef size_t (*hash_func_t)(const void* key);
typedef int (*hash_action_func_t)(void* data, void* param);
typedef int (*hash_cmp_func_t)(const void* data1, const void* data2);
/******************************************************************************/

/******************************************************************************/
/*                          Hash Functions Declaration                        */
/******************************************************************************/
/*  -Creates new hash table.
    -Returns pointer to created hash table. */
hash_t *HASHCreate(hash_func_t func, hash_cmp_func_t cmp_func, size_t table_size); 

/*  -Destroys hash table. */
void HASHDestroy(hash_t *hash);

/*  -Insert new data to hash table.
    -boolean function that returns:
       0 for success.
       1 for failure.   */
int HASHInsert(hash_t *hash, const void* data);

/*  -Removes element with <data> key.
        User responsibility that element is inside hash table. */
void HASHRemove(hash_t *hash, const void *data);

/*  -Returns number of elements in hash table.  */
size_t HASHSize(const hash_t *hash);

/*  -Checks if hash table is empty.
    -boolean function that returns:
        0 if not empty.
        1 if empty. */
int HASHIsEmpty(const hash_t *hash);

/*  -Find data in hash table. 
    -Returns data found.   */
void *HASHFind(const hash_t *hash, const void *data);

/*  -Perform action_function on each element in hash table.
    -Returns status for:
        0 for success.
        1 for failure.  */
int HASHForEach(hash_t *hash, hash_action_func_t action_func, void *param);
/******************************************************************************/

#endif /* __HASH_H__ */