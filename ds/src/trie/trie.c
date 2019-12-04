#include <stdlib.h> /* malloc   */
#include <stddef.h> /* size_t   */
#include <stdint.h> /* uint32_t */
#include <assert.h> /* assert   */
#include <stdio.h>  /* perror   */

#include "trie.h"   /* Trie API */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

struct trie_node
{
    size_t free_children_num;
    trie_node_t *children[2];
    void *data;

};

struct trie
{
    size_t height;
    trie_node_t *root;
};

typedef enum{SUCCESS = 0, FAILURE} status_t;
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

/*  -Create new node.
    -Return pointer to that node.       */
static trie_node_t *HelperCreateNode(size_t height, void *data);

/*  -Calculate number of free children. 
        2^(height + 1) - 2. Since height starts from 0. 
    -Return number of free children.    */
static size_t HelperGetFreeChildren(size_t height);

/*  -Update number of children of each node. */
static void HelperUpdateChildren(trie_node_t *node, size_t height);

/*  -Recursively insert node. */
static trie_node_t *HelperRecursiveInsert(trie_node_t *node,
                                    void *data,
                                    uint32_t path,
                                    size_t height,
                                    status_t *status);

/*  -Recursively find next free node. */
static int HelperRecursiveNextFree(trie_node_t *node,
                                    size_t height,
                                    uint32_t *path);

/*  -Recursively remove node. */
static trie_node_t *HelperRecursiveRemove(trie_node_t *node,
                                    uint32_t path,
                                    size_t height);   

/*  -Recursively destroy trie. */  
static void HelperRecursiveDestroy(trie_node_t *node);                               
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
            perror("Malloc failed in TrieCreate trie.\n");
            break;
        }

        new_trie->root = HelperCreateNode(height, NULL);
        if(NULL == new_trie->root)
        {
            perror("Malloc failed in TrieCreate root.\n");
            break;
        }

        new_trie->root->free_children_num = HelperGetFreeChildren(height);
        new_trie->root->children[0] = NULL;
        new_trie->root->children[1] = NULL;
        new_trie->root->data = NULL;

        new_trie->height = height;
    
        return new_trie;
    }

    free(new_trie->root);
    new_trie->root = NULL;

    free(new_trie);
    new_trie = NULL;

    return NULL;
}

int TrieInsert(trie_t *trie, uint32_t path, void *data)
{
    status_t status = SUCCESS;

    assert(NULL != trie);

    trie->root = HelperRecursiveInsert(trie->root,
                                        data,
                                        path,
                                        trie->height,
                                        &status);

    return status;
}

int TrieFindNextFree(trie_t *trie, uint32_t *next_free)
{
    assert(NULL != trie);

    return HelperRecursiveNextFree(trie->root,
                                    trie->height,
                                    next_free);
}

void TrieRemove(trie_t *trie, uint32_t addr)
{
    assert(NULL != trie);

    HelperRecursiveRemove(trie->root, addr, trie->height);
}

void TrieDestroy(trie_t *trie)
{
    HelperRecursiveDestroy(trie->root);

    free(trie);
    trie = NULL;
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static trie_node_t *HelperCreateNode(size_t height, void *data)
{
    trie_node_t *new_node = NULL;

    while (1)
    {
        new_node = (trie_node_t*)malloc(sizeof(*new_node));
        if (NULL == new_node)
        {
            perror("Malloc in HelperCreateNode failed.\n");
            break;
        }

        new_node->free_children_num = HelperGetFreeChildren(height);
        new_node->children[0] = NULL;
        new_node->children[1] = NULL;
        new_node->data = data;

        return new_node;
    }

    free(new_node);
    new_node = NULL;

    return NULL;
}

static size_t HelperGetFreeChildren(size_t height)
{
    /* number of children (2^(height + 1 ) - 2) */
    return ((1UL << (height + 1)) - 2);
}


static void HelperUpdateChildren(trie_node_t *node, size_t height)
{
    int left_child = 0;
    int right_child = 0;

    /* number of free children -> (2^height - 1) */
    left_child = node->children[0] == NULL ? 
                (1U << height) - 1 : node->children[0]->free_children_num; 
    right_child = node->children[1] == NULL ?
                (1U << height) - 1 : node->children[1]->free_children_num;

    node->free_children_num = left_child + right_child;
}

static trie_node_t *HelperRecursiveInsert(trie_node_t *node,
                                    void *data,
                                    uint32_t path,
                                    size_t height,
                                    status_t *status)
{
    unsigned char curr_bit = 0;

    /* reached requested location by path */
    if(0 == height)
    {
        /* node already exists - meaning ins't free */
        if(NULL != node)
        {
            return NULL;
        }
        /* if node is NULL -> empty (doesnt exists) -> create*/
        node = HelperCreateNode(height, data);
        if(NULL == node)
        {
            *status = FAILURE;   
        }

        return node;
    }

    /* go by <path> and create nodes that don't exist 
        create the path of nodes. */
    if(NULL == node)
    {
        node = HelperCreateNode(height, data);
        if(NULL == node)
        {
            *status = FAILURE;

            return NULL;
        }
    }

    /* go left or right (0/1) depends on <path> value. */
    curr_bit = 1U & (path >> (height - 1));
    /* reduce from height -1 since we moved 1 step deeper */
    node->children[curr_bit] = HelperRecursiveInsert(node->children[curr_bit],
                                                    data,
                                                    path,
                                                    height - 1,
                                                    status);

    /* if success update number of children of each node */
    if(SUCCESS == *status)
    {
        HelperUpdateChildren(node, height);
    }

    return node;
}

static int HelperRecursiveNextFree(trie_node_t *node,
                                    size_t height,
                                    uint32_t *path)
{
    int status = 0;

    /* if node doesnt have free children -> return 1. */
    if(0 == node->free_children_num)
    {
        return 1;
    }
    /* if node's left child doesnt exists -> return 0. */
    if(NULL == node->children[0])
    {
        return 0;
    }

    /* recursively go deeper into the tree */
    status = HelperRecursiveNextFree(node->children[0],
                                    height - 1,
                                    path);

    if(1 == status)
    {
        /* update path we are going on */
        *path |= 1U << (height - 1);

        /* if node's right child doesnt exists -> return 0. */
        if(NULL == node->children[1])
        {
            return 0;
        }

        return HelperRecursiveNextFree(node->children[1],
                                        height - 1,
                                        path);
    }

    return status;
}

static trie_node_t *HelperRecursiveRemove(trie_node_t *node,
                                    uint32_t path,
                                    size_t height)
{
    unsigned char curr_bit = 0;

    /* reached end of path */
    if(0 == height)
    {
        free(node);
        node = NULL;

        return NULL;
    }

    curr_bit = 1U & (path >> (height - 1));
    node->children[curr_bit] = HelperRecursiveRemove(node->children[curr_bit],
                                                    path,
                                                    height - 1);
    HelperUpdateChildren(node, height);

    return node;
}

static void HelperRecursiveDestroy(trie_node_t *node)
{
    if(NULL == node)
    {
        return;
    }

    HelperRecursiveDestroy(node->children[0]);
    HelperRecursiveDestroy(node->children[1]);

    free(node);
    node = NULL;
}
/******************************************************************************/