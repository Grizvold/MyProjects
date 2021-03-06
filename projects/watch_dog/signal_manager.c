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
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>


#include "sched.h"
#include "signal_manager.h"

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

typedef struct
{
    char **argv;          /* path to requested executable */
    pid_t pid_to_send_to; /* pid of calling process */
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

/* TODO: rewrite */
/*  -Stop running tasks and destroy sched.  */
static int TaskStop(void *data);
/******************************************************************************/

/******************************************************************************/
/*                          Signal_Manager Functions Definition               */
/******************************************************************************/

void SchedularActivate(char **argv, pid_t pid)
{
    sched_signal_t new_signal = {NULL};
    sched_t *new_sched = NULL;
    sem_t *protecting_sem = NULL;

    new_signal.argv = argv;
    new_signal.pid_to_send_to = pid;

    new_sched = SchedCreate();

    /* TODO: remove sleep */
    sleep(2); 

    SchedAddTask(new_sched,
                 atol(getenv("WATCH_DOG_FREQUENCY")),
                 TaskSignalSend,
                 &new_signal);
    SchedAddTask(new_sched,
                 atol(getenv("WATCH_DOG_FREQUENCY")),
                 TaskSignalCheck,
                 &new_signal);

    protecting_sem = sem_open("protecting_sem", O_RDWR);
    sem_post(protecting_sem);
    sem_close(protecting_sem);



    SchedRun(new_sched);
    SchedDestroy(new_sched);
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static int TaskSignalSend(void *data)
{
    kill(((sched_signal_t *)data)->pid_to_send_to, SIGUSR1);

    return 1;
}

static int TaskSignalCheck(void *data)
{
    pid_t pid;
    char *env_counter_str = NULL;
    size_t counter = 0;
    struct timespec ts = {0};
    sem_t *time_sem = NULL;
    int status = 0;

    env_counter_str = getenv("WATCH_DOG_SIGNAL_COUNTER");
    printf("counter: %d\n", atoi(env_counter_str));
    /* if counter reached 0 */
    if (0 == strcmp(env_counter_str, "0"))
    {
        pid = fork();
        while (0 > pid)
        {
            pid = fork();
        }

        if (0 == pid)
        {
            printf("program path for wd: %s \n", *((sched_signal_t *)data)->argv);
            if (0 > execvp(*(((sched_signal_t *)data)->argv), ((sched_signal_t *)data)->argv))
            {
                perror("execvp failed in TaskSignalCheck");
            } 

        }
        ((sched_signal_t *)data)->pid_to_send_to = pid;
        /* TODO: remove */
        /* TODO: semaphore for program to get ready */
            clock_gettime(CLOCK_REALTIME,&ts);
            ts.tv_sec += atoi(getenv("WATCH_DOG_GRACE"));
        
            time_sem = sem_open("time_sem", O_RDWR);
            status = sem_timedwait(time_sem, &ts);
            if(-1 == status)
            {
                perror("time_sem semaphore failure");
            }

            sem_close(time_sem);
    }
    else
    {
        counter = atoi(env_counter_str);
        counter--;

        sprintf(temp_buffer, "%ld", counter);
        setenv("WATCH_DOG_SIGNAL_COUNTER", temp_buffer, 1);
    }

    return 1;
}

static int TaskStop(void *data)
{
    return 0;
}
/******************************************************************************/