/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Sigal Galker                                                     */
/* Group: OL767                                                               */
/* Description: Program implementation, write every time-interval to file.    */
/******************************************************************************/

#include <stdio.h>      /* fopen         */
#include <time.h>       /* time func     */
#include <sys/types.h>  /* time_t        */
#include <unistd.h>     /* sleep         */
#include <pthread.h>    /* pthread_t     */

#include "sched.h"      /* Schedular API */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

typedef enum{SUCCESS = 0, FAILURE} status_t;
/******************************************************************************/


/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/


/*  -Write to file every x seconds. */
static int WriteToFile();
/******************************************************************************/


int main()
{
    WriteToFile();

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static int WriteToFile()
{
    size_t i; 
    time_t current_time;
    struct tm *timeinfo; 
    char *name_of_file = '\0';
    FILE *ptr_program_output_file = NULL;

    name_of_file = "program_output.txt";
    ptr_program_output_file = fopen(name_of_file, "w");
    if(NULL == ptr_program_output_file)
    {
        printf("\n%sError opening file%s %s \n", SET_RED_COLOR, 
                                                RESET_COLOR, 
                                                name_of_file);
    }

    for(i = 0; i < 10; i++)
    {
        time(&current_time);
        timeinfo = localtime(&current_time);
        fprintf(ptr_program_output_file, "%s", asctime(timeinfo));
        sleep(1);
    }

    if(0 == fclose(ptr_program_output_file))
    {
        ptr_program_output_file = NULL;
        printf("\n%sFile%s %s %s was successfully closed%s\n", SET_BLUE_COLOR, 
                                                            RESET_COLOR, 
                                                            name_of_file, 
                                                            SET_BLUE_COLOR, 
                                                            RESET_COLOR);

    }

    return SUCCESS;
}
/******************************************************************************/
