#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* perror       */
#include <assert.h> /* assert       */
#include <stddef.h> /* size_t       */

#include "avl.h"

#define COUNT 7 /* spaces for AVLPrintTree */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
typedef enum
{
    LEFT,
    RIGHT
} son_t;

typedef enum
{
    SUCCESS,
    FAILURE
} status_t;

typedef struct avl_node avl_node_t;

struct avl_node
{
    void *data;
    size_t height;
    avl_node_t *child[2];
};

struct avl
{
    avl_is_before_t func;
    void *func_param;
    avl_node_t *root;
};
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/
/* is_before function of AVL tree */
static int AVLHelperIsBefore(const avl_t *avl_tree,
                             const void *data_1,
                             const void *data_2);
/* prints AVL tree in 2d, to help visualize the tree */
static void AVLHelperPrintTree2D(avl_node_t *root, int space);
/* upgrades node height by looking at it's highest child and adding + 1  */
static void AVLHelperNodeHeighUpdate(avl_node_t *curr_node);
/* frees requested node */
static void AVLHelperFreeNode(avl_node_t *node);
/* comparison function between 2 const data variables */
static int AVLHelperIsSameData(const avl_t *tree,
                               const void *data_1,
                               const void *data_2);
/* creates new node and initialize values */
static avl_node_t *AVLHelperCreateNewNode(const void *data);
/* swap data between 2 nodes */
static void AVLHelperSwapData(avl_node_t *node_1, avl_node_t *node_2);
/* calculate: 
  "Balance Factor" of node - Height(RightSubtree(N) - Height(LeftSubtree(N)) */
static int AVLHelperGetBalanceFactor(avl_node_t *node);
/* get height of child on spesific side */
static size_t AVLHelperGetChildHeight(avl_node_t *node, son_t child_side);

static avl_node_t *AVLRecGetMostLeftChild(avl_t *tree, avl_node_t *node);
static avl_node_t *AVLRecInsert(avl_t *tree,
                                avl_node_t *parent,
                                avl_node_t *new_node);
static int AVLRecForEach(avl_node_t *node, avl_action_func_t func, void *param);
static void *AVLRecFind(const avl_t *tree, avl_node_t *node, const void *data);
static size_t AVLRecSize(avl_node_t *node);
static void AVLRecDestroy(avl_node_t *node);
static avl_node_t *AVLRecRemove(avl_t *tree,
                                avl_node_t *node,
                                const void *data);
/******************************************************************************/
/*                          Balancing Components Declaration                  */
/******************************************************************************/
/* balance current node */
static avl_node_t *AVLHelperBalanceNode(avl_node_t *node);
/* Left Rotation */
static avl_node_t *AVLHelperRotateLeft(avl_node_t *node);
/* Right Rotation */
static avl_node_t *AVLHelperRotateRight(avl_node_t *node);
/* Right-Left Rotation */
static avl_node_t *AVLHelperRotateRightLeft(avl_node_t *node);
/* Left-Right Rotation */
static avl_node_t *AVLHelperRotateLeftRight(avl_node_t *node);
/******************************************************************************/

/******************************************************************************/
/*                          AVL Functions Definition                          */
/******************************************************************************/
avl_t *AVLCreate(avl_is_before_t func, void *param)
{
    avl_t *new_tree = NULL;

    while (1)
    {
        new_tree = (avl_t *)malloc(sizeof(*new_tree));
        if (NULL == new_tree)
        {
            perror("Malloc failed in AVLCreate");

            break;
        }

        new_tree->func = func;
        new_tree->func_param = param;
        new_tree->root = NULL;

        return new_tree;
    }

    return NULL;
}

int AVLInsert(avl_t *tree, const void *data)
{
    avl_node_t *new_node = NULL;

    new_node = AVLHelperCreateNewNode(data);
    if (NULL == new_node)
    {

        return FAILURE;
    }

    tree->root = AVLRecInsert(tree, tree->root, new_node);
    AVLHelperNodeHeighUpdate(tree->root);

    return SUCCESS;
}

void AVLRemove(avl_t *tree, const void *data)
{
    tree->root = AVLRecRemove(tree, tree->root, data);
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(NULL != tree);

    return (NULL == tree->root);
}

size_t AVLHeight(const avl_t *tree)
{
    assert(NULL != tree);

    return tree->root->height;
}

int AVLForEach(avl_t *tree, avl_action_func_t func, void *param)
{
    return AVLRecForEach(tree->root, func, param);
}

void *AVLFind(const avl_t *tree, const void *data)
{
    return AVLRecFind(tree, tree->root, data);
}

size_t AVLSize(const avl_t *tree)
{

    return AVLRecSize(tree->root);
}

void AVLDestroy(avl_t *tree)
{
    assert(NULL != tree);

    AVLRecDestroy(tree->root);

    free(tree);
}

/******************************************************************************/

/******************************************************************************/
/*                      Internal Component Definition                         */
/******************************************************************************/
static int AVLHelperIsBefore(const avl_t *avl_tree,
                             const void *data_1,
                             const void *data_2)
{
    return avl_tree->func(data_1, data_2, avl_tree->func_param);
}

static void AVLHelperNodeHeighUpdate(avl_node_t *curr_node)
{
    size_t right_son_height = 0;
    size_t left_son_height = 0;

    /* get height of children (if no child -> height = 0) */
    right_son_height = (NULL == curr_node->child[RIGHT]) ? 0 : curr_node->child[RIGHT]->height;
    left_son_height = (NULL == curr_node->child[LEFT]) ? 0 : curr_node->child[LEFT]->height;

    /* increase the height of current node by 1 */
    curr_node->height = (right_son_height > left_son_height) ? right_son_height + 1 : left_son_height + 1;
}

static int AVLHelperGetBalanceFactor(avl_node_t *node)
{
    return (int)(AVLHelperGetChildHeight(node, RIGHT) -
                 AVLHelperGetChildHeight(node, LEFT));
}

static size_t AVLHelperGetChildHeight(avl_node_t *node, son_t child_side)
{
    return (NULL == node->child[child_side]) ? 0 : node->child[child_side]->height;
}

static int AVLHelperIsSameData(const avl_t *tree, const void *data_1,
                               const void *data_2)
{
    return (!AVLHelperIsBefore(tree, data_1, data_2) &&
            !AVLHelperIsBefore(tree, data_2, data_1));
}

static void AVLHelperSwapData(avl_node_t *node_1, avl_node_t *node_2)
{
    void *temp_data = NULL;

    temp_data = node_1->data;
    node_1->data = node_2->data;
    node_2->data = temp_data;
}

static avl_node_t *AVLRecGetMostLeftChild(avl_t *tree, avl_node_t *node)
{

    return (NULL == node->child[LEFT]) ? node : AVLRecGetMostLeftChild(tree, node->child[LEFT]);
}

static void AVLHelperFreeNode(avl_node_t *node)
{
    node->data = NULL;
    node->child[RIGHT] = NULL;
    node->child[LEFT] = NULL;

    free(node);
}

static avl_node_t *AVLHelperCreateNewNode(const void *data)
{
    avl_node_t *new_node = NULL;

    while (1)
    {
        new_node = (avl_node_t *)malloc(sizeof(*new_node));
        if (NULL == new_node)
        {
            perror("Malloc in failed in AVLHelperCreateNewNode");

            break;
        }

        new_node->data = (void *)data;
        new_node->height = 1;
        new_node->child[RIGHT] = NULL;
        new_node->child[LEFT] = NULL;

        return new_node;
    }

    return NULL;
}

static avl_node_t *AVLRecInsert(avl_t *tree, avl_node_t *parent,
                                avl_node_t *new_node)
{
    son_t side = LEFT;

    if (NULL == parent)
    {

        return new_node;
    }

    side = AVLHelperIsBefore(tree, parent->data, new_node->data);
    parent->child[side] = AVLRecInsert(tree, parent->child[side], new_node);
    AVLHelperNodeHeighUpdate(parent);
    parent = AVLHelperBalanceNode(parent);

    return parent;
}

static int AVLRecForEach(avl_node_t *node, avl_action_func_t func, void *param)
{
    /* perform action function on nodes in-order (left - root -right) */
    status_t cur_status = SUCCESS;

    if (NULL != node->child[LEFT])
    {
        cur_status = AVLRecForEach(node->child[LEFT], func, param);
    }

    if (FAILURE != cur_status)
    {
        cur_status = func(node->data, param);
    }

    if (NULL != node->child[RIGHT] && FAILURE != cur_status)
    {
        cur_status = AVLRecForEach(node->child[RIGHT], func, param);
    }

    return cur_status;
}

static void *AVLRecFind(const avl_t *tree, avl_node_t *node, const void *data)
{
    /* if current node is empty */
    if (NULL == node)
    {

        return NULL;
    }

    /* Check data of current node */
    if (AVLHelperIsSameData(tree, node->data, data))
    {

        return node->data;
    }

    else
    {
        /* Go Right if (node->data) < (data), Left otherwise */
        return AVLRecFind(tree,
                          node->child[AVLHelperIsBefore(tree, node->data, data)],
                          data);
    }
}

static size_t AVLRecSize(avl_node_t *node)
{
    if (NULL == node)
    {
        return 0;
    }

    return 1 + AVLRecSize(node->child[LEFT]) + AVLRecSize(node->child[RIGHT]);
}

static void AVLRecDestroy(avl_node_t *node)
{
    /* Destroying by post-order (left - right - root) */
    if (NULL == node)
    {

        return;
    }

    AVLRecDestroy(node->child[LEFT]);

    AVLRecDestroy(node->child[RIGHT]);

    AVLHelperFreeNode(node);
}

static avl_node_t *AVLRecRemove(avl_t *tree, avl_node_t *node, const void *data)
{
    son_t son = LEFT;
    avl_node_t *return_node = NULL;

    return_node = node;

    son = AVLHelperIsBefore(tree, node->data, data);

    /* search for convicted node with requested data */
    if (!AVLHelperIsSameData(tree, node->data, data))
    {
        /* if data not found, keep searching */
        node->child[son] = AVLRecRemove(tree, node->child[son], data);

        /* update height of nodes */
        AVLHelperNodeHeighUpdate(node);
        /* balance ret_node on every step of recursion */
        return_node = AVLHelperBalanceNode(return_node);

        return return_node;
    }
    /* if  convicted node has no children */
    if (NULL == node->child[LEFT] && NULL == node->child[RIGHT])
    {
        AVLHelperFreeNode(node);
        node = NULL;

        return NULL;
    }
    /* if convicted node has 2 children */
    else if (NULL != node->child[RIGHT] && NULL != node->child[LEFT])
    {
        /* swap data between convicted node and replacer */
        /* replacer - go right 1 step, and get most left child */
        AVLHelperSwapData(node, AVLRecGetMostLeftChild(tree, node->child[RIGHT]));

        /* continue with recursion */
        node->child[RIGHT] = AVLRecRemove(tree, node->child[RIGHT], data);
        AVLHelperNodeHeighUpdate(node);
    }
    /* if convicted node has 1 child (left or right) */
    else
    {
        return_node = (NULL != node->child[RIGHT]) ? node->child[RIGHT] : node->child[LEFT];
        AVLHelperFreeNode(node);
        node = NULL;
    }

    return AVLHelperBalanceNode(return_node);
}

/******************************************************************************/

void AVLTreePrint(const avl_t *tree)
{
    AVLHelperPrintTree2D(tree->root, 0);
}

/*  Function to print binary tree in 2D  */
/*  It does reverse inorder traversal */
static void AVLHelperPrintTree2D(avl_node_t *root, int space)
{
    /* Base case  */
    if (root == NULL)
        return;

    /*  Increase distance between levels  */
    space += COUNT;

    /*  Process right child first  */
    AVLHelperPrintTree2D(root->child[RIGHT], space);

    /*  Print current node after space count */
    printf("\n");
    printf("%*c", space, ' ');
    printf("%d\n", *((int *)root->data));

    /*  Process left child  */
    AVLHelperPrintTree2D(root->child[LEFT], space);
}

/******************************************************************************/

/******************************************************************************/
/*                      Balancing Components Definition                       */
/******************************************************************************/
static avl_node_t *AVLHelperBalanceNode(avl_node_t *node)
{
    switch (AVLHelperGetBalanceFactor(node))
    {
    /* LEFT or RIGHT-LEFT rotation */
    case 2:
        /* if balance of right-left child is "left-heavy" -> ROTATE RIGHT-LEFT */
        if (0 > AVLHelperGetBalanceFactor(node->child[RIGHT]))
        {
            node = AVLHelperRotateRightLeft(node);
        }
        /* if balance of right-right child is "right-heavy" -> ROTATE LEFT */
        else
        {
            node = AVLHelperRotateLeft(node);
        }

        break;

    case -2:
        /* Mirror mode */
        /* if balance of left-right child is "right-heavy" -> ROTATE LEFT-RIGHT */
        if (0 < AVLHelperGetBalanceFactor(node->child[LEFT]))
        {
            node = AVLHelperRotateLeftRight(node);
        }
        /* if balance of left-left child is "left-heavy" -> ROTATE LEFT-LEFT */
        else
        {
            node = AVLHelperRotateRight(node);
        }

        break;

    default:
        break;
    }

    return node;
}

/* Left Rotation */
static avl_node_t *AVLHelperRotateLeft(avl_node_t *node)
{
    avl_node_t *replacer_node = NULL;

    replacer_node = node->child[RIGHT];

    node->child[RIGHT] = replacer_node->child[LEFT];
    replacer_node->child[LEFT] = node;

    AVLHelperNodeHeighUpdate(node);
    AVLHelperNodeHeighUpdate(replacer_node);

    return replacer_node;
}

/* Right Rotation */
static avl_node_t *AVLHelperRotateRight(avl_node_t *node)
{
    avl_node_t *replacer_node = NULL;

    replacer_node = node->child[LEFT];

    node->child[LEFT] = replacer_node->child[RIGHT];
    replacer_node->child[RIGHT] = node;

    AVLHelperNodeHeighUpdate(node);
    AVLHelperNodeHeighUpdate(replacer_node);

    return replacer_node;
}

/* Right-Left Rotation */
static avl_node_t *AVLHelperRotateRightLeft(avl_node_t *node)
{
    avl_node_t *replacer_node = NULL;

    /* make right rotation, then left */
    node->child[RIGHT] = AVLHelperRotateRight(node->child[RIGHT]);
    replacer_node = AVLHelperRotateLeft(node);

    return replacer_node;
}

/* Left-Right Rotation */
static avl_node_t *AVLHelperRotateLeftRight(avl_node_t *node)
{
    avl_node_t *replacer_node = NULL;

    /* make left rotation, then right */
    node->child[LEFT] = AVLHelperRotateLeft(node->child[LEFT]);
    replacer_node = AVLHelperRotateRight(node);

    return replacer_node;
}
/******************************************************************************/