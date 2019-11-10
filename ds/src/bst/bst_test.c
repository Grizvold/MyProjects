#include <stdio.h>  /* printf       */
#include <stdlib.h> /* time         */
#include <time.h>   /* srand, rand  */
#include <string.h> /* strcmp       */
#include <assert.h> /* assert       */

#include "bst.h"

#define AMOUNT (10)
#define SET_RED_COLOR "\033[0;31m"  
#define RESET_COLOR "\033[0m"

/******************************* Typedefs *************************************/
static int IsBeforeFunc(const void *data_1,const void *data_2, void *param);

typedef struct person
{
    unsigned int id;
    unsigned int key;
}person_t;

static char *param_g[] = {"id", "key"};
/******************************************************************************/

/************************** Auxiliary Component *******************************/
static unsigned int GenerateUnsingedInt(unsigned int low_limit, 
                                        unsigned int hight_limit);
static void PersonPrint(person_t *list_of_persons);
/******************************************************************************/

int main()
{
    person_t *list_of_persons = NULL;
    size_t i = 0;

    /* put seed for random number generation */
    srand(time(NULL));
    
    list_of_persons = (person_t *)malloc(sizeof(list_of_persons) * AMOUNT);
    assert(NULL != list_of_persons);

    for(i = 0; i < AMOUNT; i++)
    {
        list_of_persons[i].key = GenerateUnsingedInt(0 , 100);
        list_of_persons[i].id = GenerateUnsingedInt(200000000, 300000000);
    }

    PersonPrint(list_of_persons);

    /* Test Is_Before_Function */
    printf("\n Test IsBeforeFunction\n");
    printf("\n by %sid%s %u\n", SET_RED_COLOR, RESET_COLOR, 
            IsBeforeFunc(&list_of_persons[0], &list_of_persons[1], param_g[0]));
    printf("\n by %skey%s %u\n", SET_RED_COLOR, RESET_COLOR,
            IsBeforeFunc(&list_of_persons[0], &list_of_persons[1], param_g[1]));

    return 0;
}


/************************** Typedef Functions *********************************/
static int IsBeforeFunc(const void *data_1,const void *data_2, void *param)
{
    if(0 == strcmp((char *)param, "id"))
    {
        return ((person_t *)data_1)->id < ((person_t *)data_2)->id;
    }

    else if(0 == strcmp((char *)param, "key"))
    {
        return ((person_t *)data_1)->id < ((person_t *)data_2)->key;
    }

    return -1;    
}
/******************************************************************************/

/************************** Auxiliary Component *******************************/
static unsigned int GenerateUnsingedInt(unsigned int low_limit, 
                                        unsigned int hight_limit)
{
    return (rand() % (hight_limit - low_limit)) + low_limit;
}

static void PersonPrint(person_t *list_of_persons)
{
    size_t i = 0;

    printf("\n");
    for(i = 0; i < AMOUNT; i++)
    {
        printf("%sid%s: %u\n",SET_RED_COLOR, RESET_COLOR, list_of_persons[i].id);
        printf("%skey%s: %u\n\n",SET_RED_COLOR, RESET_COLOR, list_of_persons[i].key);
    }
}
/******************************************************************************/
