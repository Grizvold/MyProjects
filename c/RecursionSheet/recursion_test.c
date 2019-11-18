#include <stddef.h> /* size_t */
#include <stdio.h> /*  printf */

#include "recursion.h"

#define SET_RED_COLOR "\033[0;31m"  
#define SET_BLUE_COLOR "\033[0;34m"
#define SET_CYAN_COLOR "\033[0;36m"
#define RESET_COLOR "\033[0m"

/******************************************************************************/
/*                      Internal Component Declaration                        */
/******************************************************************************/
#define STR_SIZE 20
static const char *TEST_STRINGS[] = {"Hello recursion", 
                                    "Testing", 
                                    "We Love Recursion", 
                                    "I want it that way"};
/******************************************************************************/


/******************************************************************************/
/*                         Test Functions Declaration                         */
/******************************************************************************/
void StrLenTest();
void StrCpyTest();
void StrCmpTest();
void StrStrTest();
void StrReverceTest();
void FibonacciTest();
/******************************************************************************/

int main()
{
    StrLenTest();

    StrCpyTest();

    StrCmpTest();

    StrStrTest();

    StrReverceTest();

    FibonacciTest();

    return 0;
}

/******************************************************************************/
/*                         Test Functions Definition                          */
/******************************************************************************/
void FibonacciTest()
{
    static const size_t fibonacci_arr[STR_SIZE] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};

    printf("\n\t%sFibonacci Test%s\n", SET_RED_COLOR, RESET_COLOR);
        /* Test 1 */
    printf("%s %ld %s\n", SET_BLUE_COLOR, Fibonacci(2), RESET_COLOR);
    printf("%s %ld %s\n\n", SET_CYAN_COLOR, fibonacci_arr[2], RESET_COLOR);

        /* Test 2 */
    printf("%s %ld %s\n", SET_BLUE_COLOR, Fibonacci(5), RESET_COLOR);
    printf("%s %ld %s\n\n", SET_CYAN_COLOR, fibonacci_arr[5], RESET_COLOR);

        /* Test 3 */
    printf("%s %ld %s\n", SET_BLUE_COLOR, Fibonacci(7), RESET_COLOR);
    printf("%s %ld %s\n\n", SET_CYAN_COLOR, fibonacci_arr[7], RESET_COLOR);
}

void StrReverceTest()
{
    static char str_test1[STR_SIZE] = "You are my fire";
    static char str_test2[STR_SIZE] = "The one desire";
    static char str_test3[STR_SIZE] = "TELL ME WHY?!";

    printf("\n\t%sStrReverceTest%s\n", SET_RED_COLOR, RESET_COLOR);
        /* Test 1 */
    printf("%s%s%s\n", SET_BLUE_COLOR, StrReverceRec(str_test1), RESET_COLOR);
    printf("%s\n\n", StrReverceRec(str_test1));

        /* Test 2 */
    printf("%s%s%s\n", SET_BLUE_COLOR, StrReverceRec(str_test2), RESET_COLOR);
    printf("%s\n\n", StrReverceRec(str_test2));

        /* Test 3 */
    printf("%s%s%s\n", SET_BLUE_COLOR, StrReverceRec(str_test3), RESET_COLOR);
    printf("%s\n\n", StrReverceRec(str_test3));
}

void StrStrTest()
{
    static char str_test1[] = "rec";
    static char str_test2[] = "llo";
    static char str_test3[] = "tt";
    static char str_test4[] = "sion";

    printf("\n\t%sStrStrTest%s\n", SET_RED_COLOR, RESET_COLOR);
        /* Test 1 */
    printf("%s%s%s\n", SET_BLUE_COLOR, str_test1, RESET_COLOR);
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[0], RESET_COLOR);
    printf("%s\n\n", StrStrRec(TEST_STRINGS[0], str_test1));

        /* Test 2 */
    printf("%s%s%s\n", SET_BLUE_COLOR, str_test2, RESET_COLOR);
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[0], RESET_COLOR);
    printf("%s\n\n", StrStrRec(TEST_STRINGS[0], str_test2));

        /* Test 3 */
    printf("%s%s%s\n", SET_BLUE_COLOR, str_test3, RESET_COLOR);
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[0], RESET_COLOR);
    printf("%s\n\n", StrStrRec(TEST_STRINGS[0], str_test3));

        /* Test 4 */
    printf("%s%s%s\n", SET_BLUE_COLOR, str_test4, RESET_COLOR);
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[0], RESET_COLOR);
    printf("%s\n\n", StrStrRec(TEST_STRINGS[0], str_test4));
}

void StrCmpTest()
{
    static char str_test1[] = "Hello recursion"; 
    static char str_test2[] = "Testing";

    printf("\n\t%sStrCmpTest%s\n", SET_RED_COLOR, RESET_COLOR);
        /* Test 1 */
    printf("%s%s%s\n", SET_BLUE_COLOR, str_test1, RESET_COLOR);
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[0], RESET_COLOR);
    printf("%d\n\n", StrCmpRec(str_test1, TEST_STRINGS[0]));

        /* Test 2 */
    printf("%s%s%s\n", SET_BLUE_COLOR, str_test2, RESET_COLOR);
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[1], RESET_COLOR);
    printf("%d\n\n", StrCmpRec(str_test2, TEST_STRINGS[1]));

        /* Test 3 */
    printf("%s%s%s\n", SET_BLUE_COLOR, str_test1, RESET_COLOR);
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[1], RESET_COLOR);
    printf("%d\n\n", StrCmpRec(str_test1, TEST_STRINGS[1]));

        /* Test 4 */
    printf("%s%s%s\n", SET_BLUE_COLOR, str_test2, RESET_COLOR);
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[0], RESET_COLOR);
    printf("%d\n\n", StrCmpRec(str_test2, TEST_STRINGS[0]));
}

void StrCpyTest()
{
    static char str_test[STR_SIZE] = "";

    printf("\n\t%sStrCpyTest%s\n", SET_RED_COLOR, RESET_COLOR);
        /* Test 1 */
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[0], RESET_COLOR);
    printf("%s\n\n", StrCpyRec(str_test, TEST_STRINGS[0]));

        /* Test 2 */
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[1], RESET_COLOR);
    printf("%s\n\n", StrCpyRec(str_test, TEST_STRINGS[1]));

        /* Test 3 */
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[2], RESET_COLOR);
    printf("%s\n\n", StrCpyRec(str_test, TEST_STRINGS[2]));

        /* Test 4 */
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[3], RESET_COLOR);
    printf("%s\n\n", StrCpyRec(str_test, TEST_STRINGS[3]));
}

void StrLenTest()
{
    printf("\n\t%sStrLenTest%s\n", SET_RED_COLOR, RESET_COLOR);
        /* Test 1 */
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[0], RESET_COLOR);
    printf("%lu\n\n", StrLenRec(TEST_STRINGS[0]));

        /* Test 2 */
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[1], RESET_COLOR);
    printf("%lu\n\n", StrLenRec(TEST_STRINGS[1]));

        /* Test 3 */
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[2], RESET_COLOR);
    printf("%lu\n\n", StrLenRec(TEST_STRINGS[2]));

        /* Test 4 */
    printf("%s%s%s\n", SET_BLUE_COLOR, TEST_STRINGS[3], RESET_COLOR);
    printf("%lu\n\n", StrLenRec(TEST_STRINGS[3]));
}
/******************************************************************************/