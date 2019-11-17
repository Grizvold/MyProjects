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
static void BSTNodeReplacer(bst_t *tree,bst_node_t *removed_node, 
                            bst_node_t *replacer_node);
static void BSTFreeNode(bst_node_t *node);
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

    for(iter.curr = tree->root, iter.tree = (bst_t *)tree;
        !BSTIterIsSame(iter, BSTEnd(tree)); 
        iter = BSTIterNext(iter))
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

int BSTForEach(bst_iter_t from, bst_iter_t to, bst_action_func_t func, void *param)
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
    while (!BSTIsEmpty(tree))
    {
        BSTRemove(BSTBegin(tree));
    }
    
    /* free tree structure */
    tree->root = NULL;
    tree->is_before = NULL;
    tree->func_param = NULL;

    free(tree);
}


bst_iter_t BSTRemove(bst_iter_t iter)
{
    bst_node_t *next = NULL;

    /* trying to remove an empty tree */
    assert(iter.curr);
    
    /* no child on the left, but can be child on the right */
    if (NULL == iter.curr->left)
    {
        BSTNodeReplacer(iter.tree, iter.curr, iter.curr->right);
    }
    /* has child on left, but no child on right */
    else if(NULL == iter.curr->right)
    {
        BSTNodeReplacer(iter.tree, iter.curr, iter.curr->left);
    }
    /* has child on left and on right */
    else
    {
        /* if we have a child in right and left lookup for the next child */
        iter.curr = iter.curr->right;
        iter = GoLeftToTheEnd(iter);
        next = iter.curr;

        /* if what we found is not direct child of iter */
        if (next->parent != iter.curr)
        {
            BSTNodeReplacer(iter.tree, next, next->right);

            /* connect right branch of removed node to replacer */
            next->right = iter.curr->right;
            next->right->parent = next;
        }

        /* for direct child of curr */
        BSTNodeReplacer(iter.tree,iter.curr, next); 

        /* connect left branch of removed node to replacer */
        next->left = iter.curr->left;
        next->left->parent = next;
    }

    
    /* release and free node */
    BSTFreeNode(iter.curr);

    return BSTIterCreate(iter.tree,next);
}
/******************************************************************************/

/*********************** Binary Search Tree Iterator **************************/
bst_iter_t BSTBegin(const bst_t *tree)
{
    assert(NULL != tree);

    if(BSTIsEmpty(tree))
    {
        return BSTEnd(tree);
    }

    return GoLeftToTheEnd(BSTIterCreate((bst_t *)tree, tree->root));
}

bst_iter_t BSTEnd(const bst_t *tree)
{
    return BSTIterCreate((bst_t *)tree, &tree->dummy);
}

bst_iter_t BSTIterNext(bst_iter_t iter)
{
    bst_node_t *parent = NULL;

    /* if there is right child -> go to him and then to most left child */
    if(NULL != iter.curr->right)
    {
        iter.curr = iter.curr->right;
        iter = GoLeftToTheEnd(iter);
    }
    /* if there is no right child -> go to parent untill current node
            is the left child of his parent. */
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

    /* if there is left child -> go to him and then to most right child */
    if(NULL != iter.curr->left)
    {
        iter.curr = iter.curr->left;
        iter = GoRightToTheEnd(iter);
    }
    /* if there is no left child -> go to parent untill current node
            is the right child of his parent. */
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

static void BSTNodeReplacer(bst_t *tree, bst_node_t *removed_node, 
                                                bst_node_t *replacer_node)
{
    /* if removed_node is the root, i.e parent is dummy */
    if (removed_node->parent == &tree->dummy)
    {
        /* now the root is replacer_noder */
        tree->root = replacer_node;
    }
    
    /* if removed_node is a left child, replacer_noder now takes its place as left child */
    if (removed_node == removed_node->parent->left)
    {
        removed_node->parent->left = replacer_node;
    }

    /* to_removed_node is a right child ,replacer_node replace_node in right side */
    else
    {
        removed_node->parent->right = replacer_node;
    }
    
    /* if replace node not nil , has parent */
    if (NULL != replacer_node)
    {
        replacer_node->parent = removed_node->parent;         
    }

}

static void BSTFreeNode(bst_node_t *node)
{
    /* clean node pointers */
    node->data = NULL;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    /* free node */
    free(node);
}
/******************************************************************************/