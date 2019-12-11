/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Hadas Jakoubovitsh                                               */
/* Group: OL767                                                               */
/* Description: Implementation of exercises: 
                                        6. Sum of number divisors by open_mp  */
/******************************************************************************/

#include <stdio.h>  /* printf   */
#include <stdlib.h> /* atoi     */ 
#include <omp.h>    /* omp parallel */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

static size_t SumOfDivisors(size_t num);

/******************************************************************************/

int main(int argc, char **argv)
{
    size_t requested_num = 0;

    (void)argc;
    requested_num = atoi(argv[1]);

    printf("\n\n%sSum of all divisors:%s %lu \n", SET_BLUE_COLOR,
                                                    RESET_COLOR,
                                                    SumOfDivisors(requested_num));

    return 0;
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static size_t SumOfDivisors(size_t num)
{
    size_t sum = 0;
    size_t i = 1;

    #pragma omp parallel for
    for (i = 1; i < num; ++i)
    {
        if (num % i == 0)
        {
            sum += i;
        }
    }

    return sum;
}
/******************************************************************************/
