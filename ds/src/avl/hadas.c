#include <stdlib.h> /* malloc , free */
#include <assert.h> /* assert */ 

#include "avl.h"

enum children{LEFT, RIGHT};

typedef struct avl_node avl_node_t;

struct avl_node
{
    void *data;
    int height;
    avl_node_t* children[2];
};

struct avl
{
    avl_is_before_t func;
    void *func_param;
    avl_node_t *root; 
};

/*********************** forward - declarations *******************/
avl_node_t* AVLCreateNode(void *data);
void UpdateHeight(avl_node_t *node);
int CountHelper(void* data, void* param);
int MatchNodeAndData(avl_node_t *node, const void* data, avl_is_before_t func, void* param);
avl_node_t* GoLeftToTheEnd(avl_node_t *node);
void SwapData(avl_node_t *child, avl_node_t *node);
avl_node_t *RotateLeft(avl_node_t *node);
avl_node_t* RotateRight(avl_node_t *node);
int IsBalanced(avl_node_t* node);
avl_node_t* AVLBalance(avl_node_t *node);

int AVLInsertRec(avl_node_t *node, avl_is_before_t func, void *param, void *data);
avl_node_t* AVLRemoveRec(avl_node_t *node, avl_is_before_t func, void *param, void *data);
int AVLForEachRec(avl_node_t *node, avl_action_func_t func, void *param);
void* AVLFindRec(avl_node_t *node, avl_is_before_t func, void *param, const void* data);
avl_node_t *AVLDestroyRec(avl_node_t *node);


/************************ API functions **************************/

avl_t* AVLCreate(avl_is_before_t func, void* param)
{
    avl_t *tree = NULL;

    assert(func);

    tree = (avl_t*)malloc(sizeof(*tree));
    if (NULL == tree)
    {
        return NULL;
    }

    tree->func = func;
    tree->func_param = param;
    tree->root = NULL;

    return tree;
}

int AVLInsert(avl_t *tree, const void* data)
{
    int status = 0;

    assert(tree && data);

    if (NULL == tree->root)
    {
       avl_node_t *node = AVLCreateNode((void *)data);
       if (NULL == node)
       {
           return 1;
       }

       tree->root = node;
       
       return 0;
    }

    status = AVLInsertRec(tree->root, tree->func, tree->func_param, (void *)data);
    tree->root = AVLBalance(tree->root);
    UpdateHeight(tree->root);

    return status;
}

size_t AVLHeight(const avl_t *tree)
{
    assert(tree);

    return tree->root->height;
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(tree);

    return (NULL == tree->root);
}


int AVLForEach(avl_t *tree, avl_action_func_t func, void *param)
{
    assert(tree && func);

    return AVLForEachRec(tree->root, func, param);
}


size_t AVLSize(const avl_t *tree)
{
    size_t counter = 0;

    assert(tree);

    AVLForEach((avl_t *)tree, CountHelper, &counter);

    return counter;
}


void AVLRemove(avl_t *tree, const void* data)
{
    assert(tree && data);

    tree->root = AVLRemoveRec(tree->root, tree->func, tree->func_param, (void *)data);
}


void* AVLFind(const avl_t *tree, const void *data)
{
    assert(tree && data);

    return AVLFindRec(tree->root, tree->func, tree->func_param, data);
}


void AVLDestroy(avl_t *tree)
{
    assert(tree);

    AVLDestroyRec(tree->root);
    free(tree);
}

/**********************************************************************/
/*                     inside functions                               */
/**********************************************************************/

int AVLInsertRec(avl_node_t *node, avl_is_before_t func, void *param, void *data)
{
    int place = 0;
    int status = 0;
    
    place = func(node->data, data, param);

    if (NULL == node->children[place])
    {
        node->children[place] = AVLCreateNode(data);
        UpdateHeight(node);

        return NULL == node->children[place];
    }

    status = AVLInsertRec(node->children[place], func, param, data);

    node->children[RIGHT] = AVLBalance(node->children[RIGHT]);
    node->children[LEFT] = AVLBalance(node->children[LEFT]);
    
    UpdateHeight(node);

    return status;
}

int AVLForEachRec(avl_node_t *node, avl_action_func_t func, void *param)
{
    int status = 0;

    if (NULL != node->children[LEFT])
    {
        AVLForEachRec(node->children[LEFT], func, param);
    }

    status = func(node->data, param);

    if (NULL != node->children[RIGHT])
    {
        AVLForEachRec(node->children[RIGHT], func, param);
    }

    return status;

}

avl_node_t* AVLRemoveRec(avl_node_t *node, avl_is_before_t func, void *param, void *data)
{
    avl_node_t* child = NULL;
    avl_node_t* return_node = NULL;
    int side = func(node->data, data, param);

    if (!MatchNodeAndData(node, data, func, param))
    {
        node->children[side] =  AVLRemoveRec(node->children[func(node->data, data, param)],func, param, data);
        node = AVLBalance(node);
        UpdateHeight(node);
        return node;
    }

    if (NULL == node->children[LEFT] && NULL == node->children[RIGHT])
    {
        free(node);
    }
    else if (NULL != node->children[LEFT] && NULL != node->children[RIGHT])
    {
        child = GoLeftToTheEnd(node->children[RIGHT]);
        SwapData(child, node);

        node->children[RIGHT] = AVLRemoveRec(node->children[RIGHT], func, param, data);
        return_node = node;   
    }
    else
    {
        return_node = (NULL != node->children[LEFT]) ? node->children[LEFT] : node->children[RIGHT];
        free(node);
    }

    return return_node;
}

void* AVLFindRec(avl_node_t *node, avl_is_before_t func, void *param, const void* data)
{
    if (NULL == node)
    {
        return NULL;
    }

    if (MatchNodeAndData(node, data, func, param))
    {
        return node->data;
    }

    return AVLFindRec(node->children[func(node->data, data, param)], func, param, data);
}

avl_node_t *AVLDestroyRec(avl_node_t *node)
{
    if (NULL != node->children[LEFT])
    {
        node->children[LEFT] = AVLDestroyRec(node->children[LEFT]);
    }

    if (NULL != node->children[RIGHT])
    {
        node->children[RIGHT] = AVLDestroyRec(node->children[RIGHT]);
    }

   free(node);

   return NULL;
}

int MatchNodeAndData(avl_node_t *node, const void* data, avl_is_before_t func, void* param)
{
    if (NULL == node)
    {
        return 0;
    }

    return !func(node->data, data, param) && !func(data, node->data, param);
}

avl_node_t* GoLeftToTheEnd(avl_node_t *node)
{
    if (NULL == node->children[LEFT])
    {
        return node;
    }
    
    return GoLeftToTheEnd(node->children[LEFT]);
}

avl_node_t* AVLCreateNode(void *data)
{
    avl_node_t *node = NULL;

    node = (avl_node_t *)malloc(sizeof(*node));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = data;
    node->height = 1;
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;

    return node;
}

void UpdateHeight(avl_node_t *node)
{
    int height1 = 0;
    int height2 = 0;

    height1 = (NULL == node->children[LEFT]) ? 0 : node->children[LEFT]->height;
    height2 = (NULL == node->children[RIGHT]) ? 0 : node->children[RIGHT]->height;

    node->height = (height1 > height2) ? height1 + 1 : height2 + 1;
}

int CountHelper(void* data, void* param)
{
    (void)data;
    (*(size_t *)param)++;

    return 0;
}

void SwapData(avl_node_t *child, avl_node_t *node)
{
    void *temp = child->data;
    child->data = node->data;
    node->data = temp;
}

avl_node_t* AVLBalance(avl_node_t *node)
{
    if(NULL == node)
    {
        return node;
    }

    if (!IsBalanced(node))
    {
        if(NULL != node->children[RIGHT] && NULL != node->children[RIGHT]->children[RIGHT])
        {
            node = RotateLeft(node);
        }
        else if(NULL != node->children[LEFT] && NULL != node->children[LEFT]->children[LEFT])
        {
            node = RotateRight(node);
        } 
        else if(NULL != node->children[RIGHT] && NULL != node->children[RIGHT]->children[LEFT])
        {
            node = RotateLeft(node);
            node = RotateRight(node);
        }
        else if (NULL != node->children[LEFT] && NULL != node->children[LEFT]->children[RIGHT])
        {
            node = RotateRight(node);
            node = RotateLeft(node);
        }
    } 

    node->children[RIGHT] = AVLBalance(node->children[RIGHT]);
    node->children[LEFT] = AVLBalance(node->children[LEFT]);
    
    return node;
} 

avl_node_t *RotateLeft(avl_node_t *node)
{
    avl_node_t *next_node = NULL;

    next_node = node->children[RIGHT];

    node->children[RIGHT] = next_node->children[LEFT];
    next_node->children[LEFT] = node;

    UpdateHeight(node);
    UpdateHeight(next_node);

    return next_node;
}

avl_node_t* RotateRight(avl_node_t *node)
{
    avl_node_t *next_node = NULL;

    next_node = node->children[LEFT];

    node->children[LEFT] = next_node->children[RIGHT];
    next_node->children[RIGHT] = node;

    UpdateHeight(node);
    UpdateHeight(next_node);

    return next_node;
}

int IsBalanced(avl_node_t* node)
{
    int height_left = 0;
    int height_right = 0;

    height_left = (NULL == node->children[LEFT]) ? 0 : node->children[LEFT]->height;
    height_right = (NULL == node->children[RIGHT]) ? 0 : node->children[RIGHT]->height;

    return (height_right - height_left) <= 1 && (height_right - height_left) >= -1;
}