/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Sigal Galker                                                     */
/* Group: OL767                                                               */
/* Description: Program implementation, write every time-interval to file.    */
/******************************************************************************/

#define _POSIX_C_SOURCE 199309L /* required for sigaction */
#include <stddef.h>     /* size_t   */
#include <pthread.h>
#include <unistd.h>     /* fork     */
#include <signal.h> 
#include <stdlib.h>     /* malloc   */
#include <stdio.h>      /* perror   */


#include "watchdog.h"   /* WatchDog API     */
#include "sched.h"      /* Schedular API    */


/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

struct watchdog
{
    pid_t pid;
    const char *path;
};

static int is_alive;

/*  -Send signal to partner. 
    -Returns status:
                    1 - to keep running.
                    0 - to stop running.    */
static int TaskSend();

/*  -Check received signal, to insure that partner is alive.    */
static int TaskCheck();

/*  -Reboots requested task.    */
static int CreateTask();
/******************************************************************************/


/******************************************************************************/
/*                          WatchDog Functions Definition                     */
/******************************************************************************/

wd_t *MakeMeImmortal(char *path, char **argv, size_t frequency, size_t grace)
{
    wd_t *watchdog_str = NULL;

    watchdog_str = malloc(sizeof(*watchdog_str));
    if(NULL == watchdog_str)
    {
        perror("Malloc failed in MakeMeImmortal\n");

        return NULL;
    }

    watchdog_str->path = path;

    switch (watchdog_str->pid = fork())
    {
    case -1:
        perror("fork failed in MakeMeImmortal\n");
        break;
    case 0:
        /* TODO: remove printf */
        printf("inside child\n");
        printf("path: %s", watchdog_str->path);
        /* child exec */
        if(0 > execvp(watchdog_str->path, argv))
        {
            perror("execvp failed in MakeMeImmortal\n");
        }
        break;
    default:
        /* calling program thread */
        /* pthread_create(&prog_sched, NULL, &ActFunction, ); */
        break;
    }
}

void LetMeDie(wd_t *watchdog)
{

}
/******************************************************************************/


/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

/* static int TaskSend()
{
    kill(partner_pid, SIGUSR1);

    return 1;
}
 */
/*static int TaskCheck()
{
    static int counter;

    if(is_alive)
    {
        is_alive = 0;
        counter = 0;
    }
    else
    {
        counter++;
    }

    if(counter == grace)
    {
        CreateTask();
    }
    
    /* to keep alive */
    /*return 1;
}*/

static int CreateTask()
{
    return 1;
}
/******************************************************************************/
