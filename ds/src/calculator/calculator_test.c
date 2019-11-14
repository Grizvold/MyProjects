#include <stdio.h> /* printf */

double Calculator(const char *expression, int *errors);

int main()
{
    static char *test_string = "4.556";
    int *errors = NULL;

    Calculator(test_string, errors);

    return 0;
}

/* /* /* #include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* strtod       */
#include <string.h> /* strcspn      */

#include "calculator.h"

char *expresion_test = "5.5+7*(3.8-1)/2.1/9+0-(3+1)";

int main()
{
    double *test_result = NULL;

    test_result = CreateResultBuffer();
    if (NULL == test_result)
    {
        return 1;
    }

    Calculator(expresion_test, test_result);

    return 0;
}



double *CreateResultBuffer()
{
    double *result_buff = NULL;
    
    result_buff = (double*)malloc(sizeof(*result_buff));

    return result_buff; /* no need for checkup here */
}
`
 */ */ */