#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef struct trie trie_t;
/******************************************************************************/

/******************************************************************************/
/*                          Trie Functions Declaration                        */
/******************************************************************************/

trie_t *TrieCreate(size_t height);

int TrieInsert(trie_t *trie, uint32_t addr, void *data);

int TrieFindNextFree(trie_t *trie, uint32_t *addr);

void TrieRemove(trie_t *trie, uint32_t addr);

void TrieDestroy(trie_t *trie);
/******************************************************************************/

#endif /* __TRIE_H__ */
