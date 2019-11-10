#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* perror       */
#include <assert.h> /* assert       */

#include "bst.h"

/******************************* Typedefs *************************************/
struct bst
{
    bst_is_before_func_t is_before;
    void *func_param;
    struct bst_node *root;
};

struct bst_node
{
    struct bst_node *parent;
    struct bst_node *right;
    struct bst_node *left;
    void *data;
};
/******************************************************************************/

/************************** Auxiliary Component *******************************/
static void BSTInitNewNode(bst_node_t *new_node, bst_node_t *parent, 
                                                    const void *data);

static int BSTIsBefore(bst_t *tree, const void *data_1, const void *data_2);

static bst_iter_t GoLeftToTheEnd(bst_iter_t curr_iter);
static bst_iter_t GoRightToTheEnd(bst_iter_t curr_iter);
/******************************************************************************/

/**************************** BST Functions ***********************************/
bst_t *BSTCreate(bst_is_before_func_t func, void *param)
{
    bst_t *new_tree = NULL;
    bst_node_t *dummy = NULL;
    bst_node_t *root = NULL;


    while(1)
    {
        new_tree = (bst_t *)malloc(sizeof(*new_tree));
        if(NULL == new_tree)
        {
            perror("Malloc BSTCreate failed, new_tree");

            break;
        }

        dummy = (bst_node_t *)malloc(sizeof(*dummy));
        if(NULL == dummy)
        {
            perror("Malloc BSTCreate failed, dummy");

            break; 
        }

        root = (bst_node_t *)malloc(sizeof(*root));
        if(NULL == root)
        {
            perror("Malloc BSTCreate failed, root");

            break; 
        }
        
        new_tree->is_before = func;
        new_tree->func_param = param;

        dummy->data = NULL;
        dummy->parent = NULL;
        dummy->left = root;
        dummy->right = NULL;

        BSTInitNewNode(root, dummy, NULL);

        return new_tree;
    }

    free(new_tree);
    free(dummy);
    free(root);

    return NULL;
}

bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
    bst_node_t *new_node = NULL;
    bst_node_t *curr_node = NULL;
    bst_node_t *parent_node = NULL;
    bst_iter_t iter = {NULL, NULL};

    new_node = (bst_node_t *)malloc(sizeof(*new_node));
    if(NULL != new_node)
    {
        perror("Malloc in BSTInsert failed");

        return BSTEnd(tree);
    }

    for(curr_node = tree->root; NULL != curr_node;)
    {
        parent_node = curr_node;

        /* smaller -> go left */
        if(1 == BSTIsBefore(tree, data, curr_node->data))
        {
            curr_node = curr_node->left; 
        }

        /* bigger -> go right */
        else if(0 == BSTIsBefore(tree, data, curr_node->data))
        {
            curr_node = curr_node->right;
        }
    }

    /* check if curr_node is root */
    if(NULL == parent_node->parent)
    {
        tree->root = new_node;
        BSTInitNewNode(new_node, tree->root, data);
        iter.tree = tree;
        iter.curr = new_node;
    }

    else if(1 == BSTIsBefore(tree, data, parent_node->data))
    {
        parent_node->left = new_node;
        BSTInitNewNode(new_node, parent_node, data);
        iter.tree = tree;
        iter.curr = new_node;
    }

    else if(0 == BSTIsBefore(tree, data, parent_node->data))
    {
        parent_node->right = new_node;
        BSTInitNewNode(new_node, parent_node, data);
        iter.tree = tree;
        iter.curr = new_node;
    }

    return iter;
}

int BSTIsEmpty(const bst_t *tree)
{
    bst_node_t *curr_node = NULL;
    int is_empty = 0;

    if(NULL != tree->root)
    {
        is_empty = 1;
    }

    return is_empty;
}

void BSTDestroy(bst_t *tree)
{

}

/******************************************************************************/

/*********************** Binary Search Tree Iterator **************************/
bst_iter_t BSTBegin(const bst_t *tree)
{

}

bst_iter_t BSTEnd(const bst_t *tree)
{

}

bst_iter_t BSTIterNext(bst_iter_t iter)
{

}

bst_iter_t BSTIterPrev(bst_iter_t iter)
{

}

void *BSTIterGetData(bst_iter_t iter)
{
    assert(NULL != iter.tree && NULL != iter.curr);

    return iter.curr->data;
}

int BSTIterIsSame(bst_iter_t iter1, bst_iter_t iter2)
{
    assert(NULL != iter1.tree && NULL != iter1.curr 
            && NULL != iter2.tree && NULL != iter2.curr);

    return (iter1.curr == iter2.curr) && (iter1.tree == iter2.tree); 
}
/******************************************************************************/

/************************** Auxiliary Component *******************************/
static void BSTInitNewNode(bst_node_t *new_node, bst_node_t *parent, 
                                                            const void *data)
{
    new_node->data = data;
    new_node->parent = parent;
    new_node->left = NULL;
    new_node->right = NULL;
}

static int BSTIsBefore(bst_t *tree, const void *data_1, const void *data_2)
{
    return tree->is_before(data_1, data_2, tree->func_param);
}

static bst_iter_t GoLeftToTheEnd(bst_iter_t curr_iter)
{
    bst_node_t *curr_node = NULL;

    for(curr_node = curr_iter.curr; 
        NULL != curr_node->left;
        curr_node = curr_node->left)
    {
    }

    curr_iter.curr = curr_node;

    return curr_iter;
}

static bst_iter_t GoRightToTheEnd(bst_iter_t curr_iter)
{
    bst_node_t *curr_node = NULL;

    for(curr_node = curr_iter.curr;
        NULL != curr_node->right;
        curr_node = curr_node->right)
    {
    }

    curr_iter.curr = curr_node;
 
    return curr_iter;
}
/******************************************************************************/