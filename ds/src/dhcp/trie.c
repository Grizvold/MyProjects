#include <stdlib.h> /* malloc   */
#include <stddef.h> /* size_t   */
#include <stdint.h> /* uint32_t */
#include <assert.h> /* assert   */
#include <stdio.h>  /* perror   */

#include "trie.h"   /* Trie API */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef struct trie_node
{
    size_t free_children_num;
    struct trie_node *children[2];
    void *data;

} trie_node_t;

struct trie
{
    size_t height;
    trie_node_t root;
};
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

/*  -Create new node.
    -Return pointer to that node.       */
static trie_node_t *TrieCreateNode(size_t height, void *data);

/*  -Calculate number of free children. 
        2^(height + 1) - 2. Since height starts from 0. 
    -Return number of free children.    */
static size_t GetFreeChildrenNum(size_t height);
/******************************************************************************/

/******************************************************************************/
/*                          Trie Functions Definition                         */
/******************************************************************************/

trie_t *TrieCreate(size_t height)
{
    trie_t *new_trie = NULL;

    while(1)
    {
        new_trie = (trie_t*)malloc(sizeof(*new_trie));
        if (NULL == new_trie)
        {
            perror("Malloc failed in TrieCreate.\n");
            break;
        }

        new_trie->root.free_children_num = GetFreeChildrenNum(height);
        new_trie->root.children[0] = NULL;
        new_trie->root.children[1] = NULL;
        new_trie->root.data = NULL;

        new_trie->height = height;
    
        return new_trie;
    }

    free(new_trie);
    new_trie = NULL;

    return NULL;
}

int TrieInsert(trie_t *trie, uint32_t addr)
{
    
}

int TrieFindNextFree(trie_t *trie, uint32_t *addr)
{

}

void TrieRemove(trie_t *trie, uint32_t addr)
{

}

void TrieDestroy(trie_t *trie)
{

}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static trie_node_t *TrieCreateNode(size_t height, void *data)
{
    trie_node_t *new_node = NULL;

    while (1)
    {
        new_node = (trie_node_t*)malloc(sizeof(*new_node));
        if (NULL == new_node)
        {
            perror("Malloc in TrieCreateNode failed.\n");
            break;
        }

        new_node->free_children_num = GetFreeChildrenNum(height);
        new_node->children[0] = NULL;
        new_node->children[1] = NULL;
        new_node->data = data;

        return new_node;
    }

    free(new_node);
    new_node = NULL;

    return NULL;
}

static size_t GetFreeChildrenNum(size_t height)
{
    return ((1UL << (height + 1)) - 2);
}
/******************************************************************************/