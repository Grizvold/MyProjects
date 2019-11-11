#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* perror       */
#include <assert.h> /* assert       */

#include "bst.h"

/******************************* Typedefs *************************************/

struct bst_node
{
    struct bst_node *parent;
    struct bst_node *right;
    struct bst_node *left;
    void *data;
};

struct bst
{
    bst_is_before_func_t is_before;
    void *func_param;
    struct bst_node *root;
    struct bst_node dummy;
};
/******************************************************************************/

/************************** Auxiliary Component *******************************/
static void BSTInitNewNode(bst_node_t *new_node, bst_node_t *parent, 
                                                    const void *data);

static int BSTIsBefore(const bst_t *tree, const void *data_1, const void *data_2);

static bst_iter_t GoLeftToTheEnd(bst_iter_t curr_iter);
static bst_iter_t GoRightToTheEnd(bst_iter_t curr_iter);
static bst_iter_t BSTIterCreate(const bst_t *tree, const bst_node_t *node);
/******************************************************************************/

/**************************** BST Functions ***********************************/
bst_t *BSTCreate(bst_is_before_func_t func, void *param)
{
    bst_t *new_tree = NULL;

    while(1)
    {
        new_tree = (bst_t *)malloc(sizeof(*new_tree));
        if(NULL == new_tree)
        {
            perror("Malloc BSTCreate failed, new_tree");

            break;
        }

        new_tree->is_before = func;
        new_tree->root = NULL;
        new_tree->func_param = param;

        return new_tree;
    }

    free(new_tree);

    return NULL;
}

bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
    bst_node_t *new_node = NULL;
    bst_node_t *curr_node = NULL;
    bst_node_t *parent_node = NULL;

    new_node = (bst_node_t *)malloc(sizeof(*new_node));
    if(NULL == new_node)
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
    if(NULL == parent_node)
    {
        tree->root = new_node;

        tree->dummy.right = NULL;
        tree->dummy.left = tree->root;
        tree->dummy.parent = NULL;
        tree->dummy.data = NULL;

        BSTInitNewNode(new_node, &tree->dummy, data);
    }

    else if(1 == BSTIsBefore(tree, data, parent_node->data))
    {
        parent_node->left = new_node;
        BSTInitNewNode(new_node, parent_node, data);
    }

    else if(0 == BSTIsBefore(tree, data, parent_node->data))
    {
        parent_node->right = new_node;
        BSTInitNewNode(new_node, parent_node, data);
    }

    return BSTIterCreate(tree, new_node);
}

int BSTIsEmpty(const bst_t *tree)
{
    return (NULL == tree->root);
}

bst_iter_t BSTFind(const bst_t *tree, void *requested_data)
{
    bst_iter_t iter = {NULL, NULL};

    for(iter = BSTBegin(tree); !BSTIterIsSame(iter, BSTEnd(tree)); iter = BSTIterNext(iter))
    {
        if(BSTIsBefore(tree, requested_data, iter.curr->data))
        {
            return BSTEnd(tree);
        }

        else if(!BSTIsBefore(tree, iter.curr->data, requested_data))
        {
            return iter;
        }
    }

    return BSTEnd(tree);
}

int BSTforEach(bst_iter_t from, bst_iter_t to, bst_action_func_t func, void *param)
{
    int status = 0;
    bst_iter_t iter = {NULL, NULL};

    for(iter = from; (0 == status) && !BSTIterIsSame(iter, to); iter = BSTIterNext(iter))
    {
        status = func(iter.curr->data, param);
    }

    return status;
}

void BSTDestroy(bst_t *tree)
{
    (void)tree;
}


bst_iter_t BSTRemove(bst_iter_t iter)
{


    return iter;
}
/******************************************************************************/

/*********************** Binary Search Tree Iterator **************************/
bst_iter_t BSTBegin(const bst_t *tree)
{
    return GoLeftToTheEnd(BSTIterCreate((bst_t *)tree, tree->root));
}

bst_iter_t BSTEnd(const bst_t *tree)
{
    return BSTIterCreate((bst_t *)tree, &tree->dummy);
}

bst_iter_t BSTIterNext(bst_iter_t iter)
{
    bst_node_t *parent = NULL;

    if(NULL != iter.curr->right)
    {
        iter.curr = iter.curr->right;
        iter = GoLeftToTheEnd(iter);
    }

    else
    {
        for(parent = iter.curr->parent; iter.curr == parent->right;)
        {
            iter.curr = parent;
            parent = parent->parent;
        }

        iter.curr = parent;
    }
    
    return iter;
}

bst_iter_t BSTIterPrev(bst_iter_t iter)
{
    bst_node_t *parent = NULL;

    if(NULL != iter.curr->left)
    {
        iter.curr = iter.curr->left;
        iter = GoRightToTheEnd(iter);
    }

    else
    {
        for(parent = iter.curr->parent; iter.curr == parent->left;)
        {
            iter.curr = parent;
            parent = parent->parent;
        }

        iter.curr = parent;
    }
    
    return iter;
}

void *BSTIterGetData(bst_iter_t iter)
{
    assert(NULL != iter.tree && NULL != iter.curr);

    return iter.curr->data;
}

int BSTIterIsSame(bst_iter_t iter1, bst_iter_t iter2)
{
    assert(NULL != iter1.tree);
    assert(NULL != iter2.tree);
    assert(NULL != iter1.curr);
    assert(NULL != iter2.curr);

    return (iter1.curr == iter2.curr) && (iter1.tree == iter2.tree); 
}
/******************************************************************************/

/************************** Auxiliary Component *******************************/
static void BSTInitNewNode(bst_node_t *new_node, bst_node_t *parent, 
                                                            const void *data)
{
    new_node->data = (void *)data;
    new_node->parent = parent;
    new_node->left = NULL;
    new_node->right = NULL;
}

static int BSTIsBefore(const bst_t *tree, const void *data_1, const void *data_2)
{
    return tree->is_before(data_1, data_2, tree->func_param);
}

static bst_iter_t GoLeftToTheEnd(bst_iter_t curr_iter)
{
    bst_node_t *curr_node = curr_iter.curr;

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
    bst_node_t *curr_node = curr_iter.curr;

    for(curr_node = curr_iter.curr;
        NULL != curr_node->right;
        curr_node = curr_node->right)
    {
    }

    curr_iter.curr = curr_node;
 
    return curr_iter;
}

static bst_iter_t BSTIterCreate(const bst_t *tree, const bst_node_t *node)
{
    bst_iter_t new_iter = {NULL, NULL};

    new_iter.curr = (bst_node_t *)node;
    new_iter.tree = (bst_t *)tree;

    return new_iter;
}
/******************************************************************************/