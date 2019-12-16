/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Sigal Galker                                                     */
/* Group: OL767                                                               */
/* Description: Program implementation, write every time-interval to file.    */
/******************************************************************************/

#include <stdio.h>      /* printf */
#include <unistd.h>     /* sleep  */

#include "watchdog.h"   /* WatchDog API */

int main()
{
    size_t i = 0;
    while(i < 5)
    {
        printf("inside watch dog\n");
        sleep(1);
        i++;
    }

    return 0;
}