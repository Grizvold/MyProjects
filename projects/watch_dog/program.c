/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Sigal Galker                                                     */
/* Group: OL767                                                               */
/* Description: Program implementation, write every time-interval to file.    */
/******************************************************************************/
#include <stdio.h>      /* fopen         */
#include <unistd.h>     /* sleep         */
#include <pthread.h>    /* pthread_t     */
#include <stdlib.h>     /* malloc, free  */
#include <time.h>

#include "sched.h"      /* Schedular API */
#include "watchdog.h"   /* WatchDog API  */

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

typedef struct file_info
{
    FILE *ptr_file;
    sched_t *sched;
    char *name_of_file;
} file_info_t;


/*  -Write to file every x seconds. */
static int WriteToFile(int argc, char **argv);
/******************************************************************************/


int main(int argc, char **argv)
{
    WriteToFile(argc, argv);

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static int WriteToFile(int argc, char **argv)
{
    wd_t *watchdog_handler = NULL;
    size_t task_frequency = 3; 
    size_t task_grace = 5;

    size_t i = 0;
    time_t current_time;
    struct tm *timeinfo; 
    file_info_t *requested_file;

    requested_file = (file_info_t *)malloc(sizeof(*requested_file));
    if(NULL == requested_file)
    {
        perror("Error in malloc");
        
        return FAILURE;
    }

    requested_file->name_of_file = "program_output.txt";
    requested_file->sched = SchedCreate(); 
    requested_file->ptr_file = fopen(requested_file->name_of_file, "w");
    if(NULL == requested_file->ptr_file)
    {
        printf("\n%sError opening file%s %s \n", SET_RED_COLOR, 
                                                RESET_COLOR, 
                                                requested_file->name_of_file);
    }

/*     time(&current_time); 
    timeinfo = localtime(&current_time);
    fprintf(requested_file->ptr_file, "%s", asctime(timeinfo));
    sleep(1); */

    
    for(i =0; i < 5; i++)
    {
        printf("%lu \n", i);
    }

    watchdog_handler = MakeMeImmortal("./watch_dog.o", 
                                        argv, 
                                        task_frequency, 
                                        task_grace);

    /* TODO:remove sleep */
    /* sleep(5); */
    puts("\nafter MMI\n");
    for(i; i < 10; i++)
    {
        printf("%lu \n", i);
    }

    if(0 == fclose(requested_file->ptr_file))
    {
        requested_file->ptr_file = NULL;
        printf("\n%sFile%s %s %s was successfully closed%s\n", SET_BLUE_COLOR, 
                                                            RESET_COLOR, 
                                                            requested_file->name_of_file, 
                                                            SET_BLUE_COLOR, 
                                                            RESET_COLOR);

    }

    free(watchdog_handler);

    return SUCCESS;
}
/******************************************************************************/
