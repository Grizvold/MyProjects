#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* perror       */
#include <assert.h> /* assert       */
#include <stddef.h> /* size_t       */

#include "avl.h"

#define COUNT 11

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
typedef enum {LEFT, RIGHT} son_t;
typedef enum {SUCCESS, FAILURE} status_t;
 

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
static int AVLIsBefore(const avl_t *avl_tree, const void *data_1, 
                            const void *data_2);
void AVLTreePrint(const avl_t *tree);
static void PrintAVLTree2D(avl_node_t *root, int space);
static void AVLNodeHeighUpgrade(avl_node_t *curr_node);

static avl_node_t *AVLCreateNewNode(const void *data);
static int RecAVLInsert(avl_t *tree, avl_node_t *node, const void *data);
static int RecAVLForEach(avl_node_t *node, avl_action_func_t func, void *param);
static void *RecAVLFind(const avl_t *tree, avl_node_t *node,const void *data);
static void RecAVLSize(const avl_t *tree, avl_node_t *node, size_t *tree_size);
static void RecAVLDestroy(avl_t *tree, avl_node_t *node);
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
        if(NULL == new_tree)
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

    /* if avl tree is empty -> init root */
    if(AVLIsEmpty(tree))
    {
        new_node = AVLCreateNewNode(data);
        if(NULL == new_node)
        {

            return FAILURE;
        }

        tree->root = new_node;

        return SUCCESS;
    }

    /* if avl tree is not empty -> insert recursively */

    return RecAVLInsert(tree, tree->root, data);;
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
    return RecAVLForEach(tree->root, func, param);
}

void *AVLFind(const avl_t *tree, const void *data)
{
    return RecAVLFind(tree, tree->root, data);
}

size_t AVLSize(const avl_t *tree)
{
    size_t avl_tree_size = 0;

    RecAVLSize(tree, tree->root, &avl_tree_size);

    return avl_tree_size;
}

void AVLDestroy(avl_t *tree)
{
    RecAVLDestroy(tree, tree->root);

    free(tree);
}

void AVLRemove(avl_t *tree, const void *data)
{

}
    
/******************************************************************************/


/******************************************************************************/
/*                      Internal Component Definition                         */
/******************************************************************************/
static int AVLIsBefore(const avl_t *avl_tree, const void *data_1, const void *data_2)
{
    return avl_tree->func(data_1, data_2, avl_tree->func_param);
}

static void AVLNodeHeighUpgrade(avl_node_t *curr_node)
{
    size_t right_son_height = 0;
    size_t left_son_height = 0;

    /* get height of children (if no child -> height = 0) */
    right_son_height = (NULL == curr_node->child[RIGHT]) ? 
                            0 : curr_node->child[RIGHT]->height;
    left_son_height = (NULL == curr_node->child[LEFT]) ? 
                            0 : curr_node->child[LEFT]->height;
    
    /* increase the height of current node by 1 */
    curr_node->height = (right_son_height > left_son_height) ? 
                            right_son_height + 1: left_son_height + 1;
}

static avl_node_t *AVLCreateNewNode(const void *data)
{
    avl_node_t *new_node = NULL;

    while(1)
    {
        new_node = (avl_node_t *)malloc(sizeof(*new_node));
        if(NULL == new_node)
        {
            perror("Malloc in failed in AVLCreateNewNode");

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


static int RecAVLInsert(avl_t *tree, avl_node_t *node, const void *data)
{
    son_t side = LEFT; /* LEFT = 0 */
    int is_success = 0;

    side = AVLIsBefore(tree, node->data, data);
    
    if(NULL == node->child[side])
    {
        node->child[side] = AVLCreateNewNode(data);

        if(NULL == node->child[side])
        {
            is_success = 1;
        }

        AVLNodeHeighUpgrade(node);

        return is_success;
    }

    is_success = RecAVLInsert(tree, node->child[side], data);

    AVLNodeHeighUpgrade(node);
    
    return is_success;
}


static int RecAVLForEach(avl_node_t *node, avl_action_func_t func, void *param)
{
    int is_success = 0;

    if(NULL != node->child[LEFT])
    {
        RecAVLForEach(node->child[LEFT], func, param);   
    }

    is_success = func(node->data, param);

    if(NULL != node->child[RIGHT])
    {
        RecAVLForEach(node->child[RIGHT], func, param);
    }

    return is_success;
}

static void *RecAVLFind(const avl_t *tree, avl_node_t *node, const void *data)
{
    /* if current node is empty */
    if(NULL == node)
    {

        return NULL;
    }
    
    /* Check data of current node */
    if(LEFT == AVLIsBefore(tree, node->data, data) && 
        LEFT == AVLIsBefore(tree, data, node->data))
        {
            return node->data;
        }

    else
    {
        /* Go Right if (node->data) < (data), Left otherwise */
        return RecAVLFind(tree, node->child[AVLIsBefore(tree, node->data, data)], data);
    }
}

static void RecAVLSize(const avl_t *tree, avl_node_t *node, size_t *avl_tree_size)
{
    /* Count number of elements in pre-order (root - left - right) */

     
}

static void RecAVLDestroy(avl_t *tree, avl_node_t *node)
{
    /* Destroying by post-order (left - right - root) */
    if(NULL != node->child[LEFT])
    {
        RecAVLDestroy(tree, node->child[LEFT]);
    }

    if(NULL != node->child[RIGHT])
    {
        RecAVLDestroy(tree, node->child[RIGHT]);
    }

    AVLRemove(tree, node->data);
}
/******************************************************************************/

void AVLTreePrint(const avl_t *tree)
{
    PrintAVLTree2D(tree->root, 0);
}

/*  Function to print binary tree in 2D  */
/*  It does reverse inorder traversal */
static void PrintAVLTree2D(avl_node_t *root, int space) 
{ 
     /* Base case  */
    if (root == NULL) 
        return; 
  
    /*  Increase distance between levels  */
    space += COUNT; 
  
    /*  Process right child first  */
    PrintAVLTree2D(root->child[RIGHT], space); 
  
    /*  Print current node after space count */ 
    printf("\n"); 
    printf("%*c", space, ' ');
    printf("%d\n", *((int *)root->data)); 
  
    /*  Process left child  */
    PrintAVLTree2D(root->child[LEFT], space); 
} 