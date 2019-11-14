#include <stdio.h>  /* printf */
#include <stdlib.h> /* strtod */

#include "vector.h"


/******************************************************************************/
/*                              Typedefs                                      */
/******************************************************************************/


/******************************************************************************/
/*                      Auxiliary Component Declaration                       */
/******************************************************************************/
static void InputParser(const char *expression);



/******************************************************************************/
/*                      Calculator Functions Declaration                      */
/******************************************************************************/
double Calculator(const char *expression, int *errors);







/******************************************************************************/
/*                      Auxiliary Component Definition                        */
/******************************************************************************/
static void InputParser(const char *expression)
{
    char *expression_cpy = NULL;
    double number = 0;

    expression_cpy = (char *)expression;

    number = strtod(expression_cpy, &expression_cpy);

    printf("%f\n", number);
}




/******************************************************************************/
/*                      Calculator Functions Definition                       */
/******************************************************************************/
double Calculator(const char *expression, int *errors)
{
    double dummy = 0;

    InputParser(expression);

    return dummy;
}