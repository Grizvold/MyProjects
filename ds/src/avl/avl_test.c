#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "avl.h"

#define SET_RED_COLOR "\033[0;31m"  
#define SET_BLUE_COLOR "\033[0;34m"
#define SET_CYAN_COLOR "\033[0;36m"
#define RESET_COLOR "\033[0m"

/******************************************************************************/
/*                          Test Functions Declaration                        */
/******************************************************************************/
static void AVLTest();
static void TestAVLInsert(int arr[], size_t arr_size, avl_t *tree);
static void TestAVLCreate(avl_t **tree);

static int IsBeforeFunc(const void *data_1, const void *data_2, void *param);
static int PrintTree(void *data, void *param);
/******************************************************************************/


int main()
{
    AVLTest();   

    return 0;
}


/******************************************************************************/
/*                          Test Functions Definition                         */
/******************************************************************************/
static int IsBeforeFunc(const void *data_1, const void *data_2, void *param)
{
    return (*(int *)data_1 < *(int *)data_2); 
}

static int PrintTree(void *data, void *param)
{
    int status = 0;

    (void)param;
    printf("%s%u, %s", SET_RED_COLOR, *(int *)data, RESET_COLOR); 

    return status;
}

static void TestAVLInsert(int arr[], size_t arr_size, avl_t *tree)
{
    size_t iter = 0;

    for(iter = 0; iter < arr_size; iter++)
    {
        AVLInsert(tree, &arr[iter]);
    }
}

static void TestAVLCreate(avl_t **tree)
{
    *tree = AVLCreate(IsBeforeFunc, NULL);
}

static void AVLTest()
{
    avl_t *avl_tree = NULL;
    size_t arr_size = 11;
    static int test_arr[] = {50, 60, 70, 55, 56, 51, 40, 45, 30, 35, 20}; /* size 11 */

    TestAVLCreate(&avl_tree);

    TestAVLInsert(test_arr, arr_size, avl_tree);

    AVLForEach(avl_tree, PrintTree, NULL);

    AVLFind(avl_tree, NULL);
}

/******************************************************************************/