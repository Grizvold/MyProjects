#include <stdlib.h>

#include "trie.h"

struct trie_node
{
    void *data;
    int free_children;
    trie_node_t *children[2];
};

struct trie
{
    int height;
    trie_node_t *root;
};

enum children
{
    LEFT,
    RIGHT
};

/************************************************************************/

void TrieRecDestroy(trie_node_t *node);
int TrieNextFreeRec(trie_node_t *node, int height, uint32_t *path);
trie_node_t *TrieInsertRec(trie_node_t *node, void *data, uint32_t path, int height, int *status);
trie_node_t *TrieRemovetRec(trie_node_t *node, uint32_t path, int height);

trie_node_t *CreateNode(void *data, int height);
void UpdateOffspring(trie_node_t *node, int height);

/*******************************************************/

trie_t *TrieCreate(int height)
{
    trie_t *new_trie = NULL;

    new_trie = (trie_t *)malloc(sizeof(*new_trie));
    if (NULL == new_trie)
    {
        return NULL;
    }

    new_trie->height = height;

    new_trie->root = CreateNode(NULL, new_trie->height);
    if (NULL == new_trie->root)
    {
        free(new_trie);
        return NULL;
    }

    return new_trie;
}

int TrieInsert(trie_t *trie, uint32_t path, void *data)
{
    int status = 0;

    trie->root = TrieInsertRec(trie->root, data, path, trie->height, &status);

    return status;
}

/***/
int TrieNextFree(trie_t *trie, uint32_t* next_free)
{
    return TrieNextFreeRec(trie->root, trie->height, next_free);
}

/**/

void TrieRemove(trie_t *trie, uint32_t path)
{
    TrieRemovetRec(trie->root, path, trie->height);
}

/***/
void TrieDestroy(trie_t *trie)
{
    TrieRecDestroy(trie->root);

    free(trie);
    trie = NULL;
}


/*********** internal functions *******************/

trie_node_t *TrieInsertRec(trie_node_t *node, void *data, uint32_t path, int height, int *status)
{
    int bit = 0;

    if (0 == height)
    {
        if (NULL != NULL)
        {
            return NULL;
        }

        node = CreateNode(data, height);
        *status = (NULL == node);
    
        return node;
    }

    if (NULL == node)
    {
        node = CreateNode(data, height);
        if (NULL == node)
        {
            *status = 1;
            return NULL;
        }
    }

    bit = 1U & (path >> (height - 1));
    node->children[bit] = TrieInsertRec(node->children[bit], data, path, height - 1, status);

    if (0 == *status)
    {
        UpdateOffspring(node, height);
    }

    return node;
}

trie_node_t *TrieRemovetRec(trie_node_t *node, uint32_t path, int height)
{
    int bit = 0;

    if (0 == height)
    {
        free(node);
        return NULL;
    }

    bit = 1U & (path >> (height - 1));
    node->children[bit] = TrieRemovetRec(node->children[bit], path, height - 1);

    UpdateOffspring(node, height);

    return node;
}

int TrieNextFreeRec(trie_node_t *node, int height, uint32_t *path)
{
    int status = 0;

    if (node->free_children == 0)
    {
        return 1;
    }

    if (NULL == node->children[0])
    {
        return 0;
    }

    status = TrieNextFreeRec(node->children[0], height - 1, path);

    if (1 == status)
    {
        *path |= 1U << (height - 1);

        if (NULL == node->children[1])
        {
            return 0;
        }

        return TrieNextFreeRec(node->children[1], height - 1, path);
    }

    return status;
}

void TrieRecDestroy(trie_node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    TrieRecDestroy(node->children[0]);
    TrieRecDestroy(node->children[1]);

    free(node);
}

trie_node_t *CreateNode(void *data, int height)
{
    trie_node_t *new_node = NULL;

    new_node = (trie_node_t *)malloc(sizeof(*new_node));
    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->free_children = (1U << (height + 1)) - 2;
    new_node->data = data;
    new_node->children[0] = NULL;
    new_node->children[1] = NULL;

    return new_node;
}

void UpdateOffspring(trie_node_t *node, int height)
{
    int left = 0;
    int right = 0;

    left = node->children[0] == NULL ? (1U << height) - 1 : node->children[0]->free_children;
    right = node->children[1] == NULL ? (1U << height) - 1 : node->children[1]->free_children;

    node->free_children = left + right;
}