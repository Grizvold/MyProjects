#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef struct trie trie_t;

typedef struct trie_node trie_node_t;
/******************************************************************************/

/******************************************************************************/
/*                          Trie Functions Declaration                        */
/******************************************************************************/

/*  -Create new trie.
    -Return pointer to new trie. */
trie_t *TrieCreate(size_t height);

/*  -Insert data to the requested <path>.
    -Return status of:
                    SUCCESS - 0
                    FAILURE - 1. */
int TrieInsert(trie_t *trie, uint32_t path, void *data);

/*  -Find next free node. 
    -Returns status of:
                    SUCCESS - 0
                    FAILURE - 1. */
int TrieFindNextFree(trie_t *trie, uint32_t *next_free);

/*  -Remove node by requested path. */
void TrieRemove(trie_t *trie, uint32_t path);

/*  -Destroy requested trie. */
void TrieDestroy(trie_t *trie);
/******************************************************************************/

#endif /* __TRIE_H__ */
