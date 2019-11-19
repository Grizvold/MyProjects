#include <stdio.h>
#include <string.h>

#include "calculator.h"

int main()
{
    char *str = "-5.3 *(-2.6 / 7.3 + 3.8) - 2.1";
    double result = 0;
    int * err = NULL;

    result = Calculator(str, err);
    printf("% f\n", result);

    return 0;
}