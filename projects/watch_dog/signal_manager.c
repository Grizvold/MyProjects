/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Sigal Galker                                                     */
/* Group: OL767                                                               */
/* Description: Creating schedular with 2 tasks: 
                                            sending and receiving signals.    */
/******************************************************************************/

#define _POSIX_C_SOURCE 200112L /* required for sigaction/env variable */
#include <stddef.h>             /* size_t   */
#include <pthread.h>            /* pthread_create */
#include <unistd.h>             /* fork     */
#include <signal.h>             /* sigaction */
#include <stdlib.h>             /* malloc, setenv   */
#include <stdio.h>              /* perror   */
#include <sys/types.h>
#include <string.h>

#include "sched.h"
#include "signal_manager.h"

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

typedef struct
{
    char **argv; /* path to requested executable */
    pid_t pid;  /* pid of calling process */
} sched_signal_t;

/*  -Char buffer for environmental variables.   */
static char temp_buffer[30];

/*  -Send signal to partner. 
    -Returns status:
                    1 - to keep running.
                    0 - to stop running.    */
static int TaskSignalSend(void *data);

/*  -Check received signal, to insure that partner is alive.    */
static int TaskSignalCheck(void *data);
/******************************************************************************/

/******************************************************************************/
/*                          Signal_Manager Functions Definition               */
/******************************************************************************/

void SchedularActivate(char **argv, pid_t pid)
{
    sched_signal_t new_signal = {NULL};
    sched_t *new_sched = NULL;

    new_signal.argv = argv;
    new_signal.pid = pid;

    new_sched = SchedCreate();

    SchedAddTask(new_sched,
                 *(size_t *)getenv("WATCH_DOG_FREQUENCY"),
                 TaskSignalSend,
                 &new_signal);
    SchedAddTask(new_sched,
                 *(size_t *)getenv("WATCH_DOG_FREQUENCY"),
                 TaskSignalCheck,
                 &new_signal);
    SchedRun(new_sched);
    SchedDestroy(new_sched);
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static int TaskSignalSend(void *data)
{
    kill(((sched_signal_t *)data)->pid, SIGUSR1);

    return 1;
}

static int TaskSignalCheck(void *data)
{
    pid_t pid;
    char *env_counter_str = NULL;
    size_t counter = 0;

    env_counter_str = getenv("WATCH_DOG_SIGNAL_COUNTER");

    /* if counter reached 0 */
    if (0 == strcmp(env_counter_str, '0'))
    {
        pid = fork();
        while (0 > pid)
        {
            pid = fork();
        }

        if (0 == pid)
        {
            if (0 > execvp(((sched_signal_t *)data)->argv, ((sched_signal_t *)data)->argv))
            {
                perror("execvp failed in TaskSignalCheck\n");
            }

            return 1;
        }
    }
    else
    {
        counter = atoi(env_counter_str);
        counter--;

        sprintf(temp_buffer, "%ld", counter);
        setenv("WATCH_DOG_SIGNAL_COUNTER", temp_buffer, 1);
    }
    

    return 0;
}
/******************************************************************************/