#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */
#include <stdlib.h>

#include "hash.h"



typedef struct person
{
    char *first_name;
    char *last_name;
    size_t id;
}person_t;

#define SIZE 10

/*colors */
#define NRM  "\x1B[0m"
#define RED  "\x1B[1;31m"
#define GRN  "\x1B[1;32m"
#define YEL  "\x1B[1;33m"

size_t HashFunc(const void *data);
int CmpFunc(const void *data1, const void *data2);
int Print(void *data, void *param);
void CreateData(person_t *data_array);

void HASHTest(hash_t*table, person_t *data_array);

void HASHInsertTest(hash_t*table, person_t *data_array);
void HASHSizeTest(hash_t*table, person_t *data_array);
void HASHForEachTest(hash_t*table, person_t *data_array);
void HASHIsEmptyTest(hash_t*table, person_t *data_array);
void HASHRemoveTest(hash_t*table, person_t *data_array);
void HASHHeightTest(hash_t*table, person_t *data_array);
void HASHFindTest(hash_t*table, person_t *data_array);

/*******************************************************************/

int main()
{   
    person_t *data_array = NULL;
    hash_t *table = NULL;

    data_array = (person_t*)malloc(sizeof(person_t) * 10);
    if (NULL == data_array)
    {
        return 1;
    }
     
    table = HASHCreate(HashFunc, CmpFunc, SIZE);
    if (NULL == table)
    {
        return 1;
    }
   
    CreateData(data_array);
    
    HASHTest(table, data_array);

    HASHDestroy(table);

    free(data_array);

    return 0;
}

/**********************************************************************/

int IsBefore(const void *data1, const void *data2, void *param)
{ 
    return (((person_t*)data1)->id < ((person_t*)data2)->id);
} 

int Print(void *data, void *param)
{
    printf("%lu -    %s  %s\n", ((person_t*)data)->id, ((person_t*)data)->first_name, ((person_t*)data)->last_name);

    return 0;
}

void CreateData(person_t *data_array)
{
    static char *first_name[SIZE] = {"hadas" , "gabriel", "ruslan", "shai", "maor",
                                    "daniela" , "sigal", "dalia", "galor", "yuval"};

    static char *last_name[SIZE] = {"edrei", "roth", "yamin", "gorbaty", "frank", "moyal", 
                            "galker", "goel", "motro", "jakobouvitsh"};

    static size_t id[SIZE] = {4626548, 1235214, 3772548, 4265637, 6532661 , 7536548,
                    5734877, 9546832 , 2573835, 2346286};

     person_t person;
     size_t i =0;

    for (i =0 ; i<SIZE; ++i)
    {
        person.first_name = first_name[i];
        person.last_name = last_name[i];
        person.id = id[i];

        data_array[i] = person;
    }
}


void HASHTest(hash_t*table, person_t *data_array)
{
    HASHInsertTest(table, data_array);
    HASHForEachTest(table, data_array);
    HASHSizeTest(table, data_array);
    HASHIsEmptyTest(table, data_array);
    HASHRemoveTest(table, data_array);
    HASHFindTest(table, data_array); 
}

void HASHInsertTest(hash_t*table, person_t *data_array)
{
    size_t i =0;

    printf("%s Insert Test: %s \n", YEL, NRM);

    for (i = 0; i < SIZE ; ++i)
    {
        HASHInsert(table, &data_array[i]);
    }

    (HASHSize(table) == SIZE) ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);
}

void HASHSizeTest(hash_t*table, person_t *data_array)
{
    printf("%s Size Test: %s\n", YEL, NRM);

    (HASHSize(table) == SIZE) ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);
    HASHRemove(table, &data_array[1]);
    (HASHSize(table) == SIZE-1) ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);
}

void HASHIsEmptyTest(hash_t*table, person_t *data_array)
{
    hash_t*new_table;

    printf("%s Is-Empty Test: %s\n", YEL, NRM);

    new_table = HASHCreate(HashFunc, CmpFunc, SIZE);

    (!HASHIsEmpty(table)) ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);
    (HASHIsEmpty(new_table)) ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);

    HASHDestroy(new_table);
}

void HASHRemoveTest(hash_t*table, person_t *data_array)
{
    printf("%s Remove Test: %s\n", YEL, NRM);

    HASHRemove(table, &data_array[0]);
    HASHRemove(table, &data_array[6]);
    HASHRemove(table, &data_array[2]);
    HASHRemove(table, &data_array[9]);

    (HASHSize(table) == SIZE-5) ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);
}


void HASHFindTest(hash_t*table, person_t *data_array)
{
    person_t find;
    person_t cant_find;

    printf("%s Find Test: %s\n", YEL, NRM);

    find.first_name = "maor";
    cant_find.first_name = "Yosi";
    printf("serching for name: \"maor\", found\n");
    Print(HASHFind(table, &find), NULL);

    (NULL == HASHFind(table, &cant_find)) ? printf("%s Success%s\n", GRN, NRM) : printf("%s Failure%s \n", RED, NRM);
    
}

void HASHForEachTest(hash_t*table, person_t *data_array)
{
    printf("%s For-Each Test: %s\n", YEL, NRM);

    printf("print the array:\n");
    HASHForEach(table, Print, NULL);
}


size_t HashFunc(const void *data)
{
    return *(int *)((person_t *)data)->first_name;
}

int CmpFunc(const void *data1, const void *data2)
{
    return !strcmp(((person_t *)data1)->first_name, ((person_t *)data2)->first_name);
}