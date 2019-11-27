#include <stdio.h>  /* printf   */
#include <string.h> /* strcmp   */
#include <stdlib.h> /* free     */
#include <time.h>   /* time     */

#include "hash.h" /* HASH API */


/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/
static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *SET_CYAN_COLOR = "\033[0;36m";
static const char *SET_GREEN_COLOR = "\033[0;32m";
static const char *RESET_COLOR = "\033[0m";

static const size_t SIZE = 10;

typedef enum{SUCCESS = 0, FAILURE} is_success_t;

typedef struct person
{
    char *first_name;
    char *last_name;
    size_t id;
} person_t;

/*  Initializing person_t struct fields. */
void CreatePerson(person_t *person_arr);
/*  Print array of perosn_t */
void PrintPersonsList(person_t *person_arr);
/*  Action function for ForEach. */
int PrintSinglePerson(void *data, void *param);

/*  HASH function that gets <key> and returns size_t value. */
size_t HASHFunction(const void *key);
/*  Compare function for HASH table. 
    Returns:
        1 if equal.
        0 if not equal. */
int CmpFunction(const void *data_1, const void *data_2);
/******************************************************************************/

/******************************************************************************/
/*                          Test Functions Declaration                        */
/******************************************************************************/
void TestHASH();
hash_t *TestHASHCreate(hash_t *hash_table);
void TestHASHInsert(hash_t *hash_table, person_t *person_arr);
void TestHASHSize(hash_t *hash_table);
void TestHASHFind(hash_t *hash_table);
void TestHASHForEach(hash_t *hash_table);
void TestHASHIsEmpty(hash_t *hash_table);
void TestHASHRemove(hash_t *hash_table);
/******************************************************************************/

int main()
{
    srand(time(NULL));

    TestHASH();

    return 0;
}

/******************************************************************************/
/*                          Test Functions Definition                        */
/******************************************************************************/
void TestHASH()
{
    static person_t *person_array = NULL;
    static hash_t *test_hash_table = NULL;

    while (1)
    {
        person_array = (person_t *)malloc(sizeof(person_t) * SIZE);
        if (NULL == person_array)
        {
            perror("Malloc creating person_array in TestHASH failed");

            break;
        }

        /* Create and Init list of persons */
        printf("\n%s\t Created list of persons:%s\n", SET_CYAN_COLOR, RESET_COLOR);
        CreatePerson(person_array);

        /*  Print list of persons */
        PrintPersonsList(person_array);

        /*  HASHCreate Test */
        printf("\n\t%s HASHCreate Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
        test_hash_table = TestHASHCreate(test_hash_table);
        if(NULL == test_hash_table)
        {
            break;
        }

        /*  HASHInsert Test */
        printf("\n\t%s HASHInsert Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
        TestHASHInsert(test_hash_table, person_array);

        /*  HASHSize Test */
        printf("\n\t%s HASHSize Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
        TestHASHSize(test_hash_table); 

        /*  HASHForEach Test */
        printf("\n\t%s HASHForEach Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
        TestHASHForEach(test_hash_table);

        /*  HASHFind Test */
        printf("\n\t%s HASHFind Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
        TestHASHFind(test_hash_table);

        /*  HASHIsEmpty Test */
        printf("\n\t%s HASHIsEmpty Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
        TestHASHIsEmpty(test_hash_table);

        /*  HASHRemove Test */
        printf("\n\t%s HASHRemove Test %s\n", SET_CYAN_COLOR, RESET_COLOR);
        TestHASHRemove(test_hash_table);

        HASHDestroy(test_hash_table);
        test_hash_table = NULL;
     
        break;
    }

    free(person_array);
    person_array = NULL;
}

hash_t *TestHASHCreate(hash_t *hash_table)
{
    hash_table = HASHCreate(&HASHFunction, &CmpFunction, SIZE);
    if(NULL == hash_table)
    {
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR, __LINE__, RESET_COLOR);

        return NULL;
    }
    else 
    {
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR);
    }

    return hash_table;
}

void TestHASHInsert(hash_t *hash_table, person_t *person_arr)
{
    size_t i = 0;
    is_success_t status = SUCCESS;

    for ( i = 0; i < SIZE; i++)
    {
        status = HASHInsert(hash_table, &person_arr[i]);

        if(FAILURE == status)
        {
            break;
        }
    }
    
    status == SUCCESS ? 
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) :
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR,
                                                 __LINE__, 
                                                 RESET_COLOR);
}

void TestHASHSize(hash_t *hash_table)
{
    (SIZE == HASHSize(hash_table)) ? 
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) :
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR,
                                                 __LINE__, 
                                                 RESET_COLOR);
}

void TestHASHForEach(hash_t *hash_table)
{
    (SUCCESS == HASHForEach(hash_table, &PrintSinglePerson, NULL)) ?
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) :
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR,
                                                 __LINE__, 
                                                 RESET_COLOR);
}

void TestHASHFind(hash_t *hash_table)
{
    person_t existing_person = {NULL};
    person_t not_existing_person = {NULL};
    int res_strcmp = 0;

    existing_person.first_name = "Ruslan";
    existing_person.last_name = NULL;
    existing_person.id = 0;
    not_existing_person.first_name = "MMMM";
    not_existing_person.last_name = NULL;
    not_existing_person.id = 0;

    res_strcmp = strcmp(existing_person.first_name, 
        ((person_t *)HASHFind(hash_table, &existing_person))->first_name);
    
    (SUCCESS == res_strcmp &&  
        NULL == HASHFind(hash_table, &not_existing_person)) ? 
            printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) :
            printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR,
                                                    __LINE__, 
                                                    RESET_COLOR);
}

void TestHASHIsEmpty(hash_t *hash_table)
{
    (SUCCESS == HASHIsEmpty(hash_table)) ?
        printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) :
        printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR,
                                                 __LINE__, 
                                                 RESET_COLOR);
}

void TestHASHRemove(hash_t *hash_table)
{
    person_t convicted_person = {NULL};

    convicted_person.first_name = "Galor";
    convicted_person.last_name = NULL;
    convicted_person.id = 0;

    HASHRemove(hash_table, &convicted_person);

    (NULL == HASHFind(hash_table, &convicted_person) &&
        SIZE - 1 == HASHSize(hash_table)) ? 
            printf("\n%s SUCCESS %s\n", SET_BLUE_COLOR, RESET_COLOR) :
            printf("\n%s FAILURE Line number:%d%s\n", SET_RED_COLOR,
                                                    __LINE__, 
                                                    RESET_COLOR);
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/
void PrintPersonsList(person_t *person_arr)
{
    size_t i = 0;

    for (i = 0; i < SIZE; i++)
    {
        printf("%s\t FirstName:%s %s \t %sLastName:%s %s \t %sID:%s %lu\n",
                SET_GREEN_COLOR, RESET_COLOR, person_arr[i].first_name,
                SET_GREEN_COLOR, RESET_COLOR, person_arr[i].last_name,
                SET_GREEN_COLOR, RESET_COLOR, person_arr[i].id);
    }
}

int PrintSinglePerson(void *data, void *param)
{
    printf("%s\t FirstName:%s %s \t %sLastName:%s %s \t %sID:%s %lu\n",
                SET_GREEN_COLOR, RESET_COLOR, ((person_t *)data)->first_name,
                SET_GREEN_COLOR, RESET_COLOR, ((person_t *)data)->last_name,
                SET_GREEN_COLOR, RESET_COLOR, ((person_t *)data)->id);

    return SUCCESS;
}

void CreatePerson(person_t *person_arr)
{
    size_t i = 0;
    static char *first_name[] = {"Hadas", "Gabriel", "Ruslan", "Shai", "Maor",
                                 "Daniela", "Sigal", "Dalia", "Galor", "Yuval"};
    static char *last_name[] = {"Edrei", "Roth", "Yamin", "Gorbaty", "Frank",
                                "Moyal", "Galker", "Goel", "Motro", "Jakbovich"};
    for (i = 0; i < SIZE; i++)
    {
        person_arr[i].first_name = first_name[i];
        person_arr[i].last_name = last_name[i];
        /* rand() % (max_number + 1 - minimum_number) + minimum_number */
        person_arr[i].id = (size_t)(rand() % (3000000 + 1 - 2000000) + 2000000);
    }
}

size_t HASHFunction(const void *key)
{
    size_t hash = 0;
    char *first_name = NULL;

    for(first_name = ((person_t *)(key))->first_name;
        '\0' != *first_name;
        first_name++)
    {
        hash = *first_name + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

int CmpFunction(const void *data_1, const void *data_2)
{
    return !strcmp(((person_t *)data_1)->first_name, ((person_t *)data_2)->first_name);
}
/******************************************************************************/
