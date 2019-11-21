#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "avl.h"

#define SET_RED_COLOR "\033[0;31m"  
#define SET_BLUE_COLOR "\033[0;34m"
#define SET_CYAN_COLOR "\033[0;36m"
#define RESET_COLOR "\033[0m"


/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/
typedef enum {SUCCESS, FAILURE} test_result_t;

static int IsBeforeFunc(const void *data_1, const void *data_2, void *param);
static int PrintTree(void *data, void *param);
/******************************************************************************/


/******************************************************************************/
/*                          Test Functions Declaration                        */
/******************************************************************************/
static void AVLTest();
static void TestAVLCreate(avl_t **tree);
static void TestAVLInsert(int arr[], size_t arr_size, avl_t *tree);
static void TestAVLForEach(avl_t *tree);
static void TestAVLFind(avl_t *tree);
static void TestAVLHeight(avl_t *tree, size_t height);
static void TestAVLSize(avl_t *tree, size_t avl_tree_size);
static void TestAVLRemove(avl_t *tree);
static void TestAVLDestroy(avl_t *tree);
/******************************************************************************/


int main()
{
    AVLTest();   

    return 0;
}


/******************************************************************************/
/*                          Test Functions Definition                         */
/******************************************************************************/

static void AVLTest()
{
    avl_t *avl_tree = NULL;
    size_t arr_size = 12; 
    size_t tree_height = 4; /* current 4 */
    static int test_arr[] = {50, 60, 70, 55, 51, 40, 45, 30, 35, 20, 80, 90}; /* size 12 */

    /* AVLCreate Test */
    printf("\n\t%s AVLCreate Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    TestAVLCreate(&avl_tree);

    /* AVLInsert Test */
    printf("\n\t%s AVLInsert Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    TestAVLInsert(test_arr, arr_size, avl_tree);

    /* AVLForEach Test */
    printf("\n\t%s AVLForEach Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    TestAVLForEach(avl_tree);
    
    /* AVLFind Test */
    printf("\n\t%s AVLFind Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    TestAVLFind(avl_tree);

    /* AVLHeight Test */
    printf("\n\t%s AVLHeight Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    TestAVLHeight(avl_tree, tree_height);

    /* AVLSize Test */
    printf("\n\t%s AVLSize Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    TestAVLSize(avl_tree, arr_size);

    /* AVLTreePrint Test */
    printf("\n\t%s AVLTreePrint Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    AVLTreePrint(avl_tree);
    printf("%s", RESET_COLOR); 
    
    /* AVLRemove Test */
    printf("\n\t%s AVLRemove Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    TestAVLRemove(avl_tree);

    /* AVLDestroy Test */
    printf("\n\t%s AVLDestroy Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
    TestAVLDestroy(avl_tree);

}


static void TestAVLCreate(avl_t **tree)
{
    *tree = AVLCreate(IsBeforeFunc, NULL);
    if(NULL != tree)
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }
}

static void TestAVLInsert(int arr[], size_t arr_size, avl_t *tree)
{
    size_t iter = 0;

    for(iter = 0; iter < arr_size; iter++)
    {
        AVLInsert(tree, &arr[iter]);
    }

    if(iter == arr_size)
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }
}

static void TestAVLForEach(avl_t *tree)
{
    if(SUCCESS == AVLForEach(tree, PrintTree, NULL))
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    } 
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }
}

static void TestAVLFind(avl_t *tree)
{
    int num_1 = 50, 
        num_2 = 80, 
        num_3 = 20, 
        num_4 = 55;

    /* Test 1 */
    if(num_1 == *(int *)AVLFind(tree, &num_1))
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }

    /* Test 2 */
    if(num_2 == *(int *)AVLFind(tree, &num_2))
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }

    /* Test 3 */
    if(num_3 == *(int *)AVLFind(tree, &num_3))
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }

    /* Test 4 */
    if(num_4 == *(int *)AVLFind(tree, &num_4))
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }
}

static void TestAVLHeight(avl_t *tree, size_t height)
{
    size_t tree_height = height;

    if(tree_height == AVLHeight(tree))
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }
}

static void TestAVLSize(avl_t *tree, size_t avl_tree_size)
{
    if(avl_tree_size == AVLSize(tree))
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }
    else
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);
    }
}

static void TestAVLRemove(avl_t *tree)
{
    int requested_data_1 = 90;
    int requested_data_2 = 55;
    int requested_data_3 = 70;

    /* Test 1 */
    printf("\n\n%sRemoving %d%s", SET_BLUE_COLOR, requested_data_1, RESET_COLOR);
    printf("%s", SET_RED_COLOR);
    AVLRemove(tree, &requested_data_1);
    AVLTreePrint(tree);

    /* Test 2 */
    printf("\n\n%sRemoving %d%s", SET_BLUE_COLOR, requested_data_2, RESET_COLOR);
    printf("%s", SET_BLUE_COLOR);
    AVLRemove(tree, &requested_data_2);
    AVLTreePrint(tree);

    /* Test 3 */
    printf("\n\n%sRemoving %d%s", SET_BLUE_COLOR, requested_data_3, RESET_COLOR);
    printf("%s", SET_CYAN_COLOR);
    AVLRemove(tree, &requested_data_3);
    AVLTreePrint(tree);
}

static void TestAVLDestroy(avl_t *tree)
{
    AVLDestroy(tree);
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
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
/******************************************************************************/
