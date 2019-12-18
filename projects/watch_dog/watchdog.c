/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Sigal Galker                                                     */
/* Group: OL767                                                               */
/* Description: MakeMeImmortal implementation & LetMeDie.                     */
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

#include "watchdog.h"       /* WatchDog API     */
#include "signal_manager.h" /* Creation of schedular with tasks */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

struct watchdog
{
    pid_t pid;
    char *path;
    pthread_t pthread_id;
};

/*  -Char buffer for environmental variables.   */
static char temp_buffer[30];

/*  -Reboots requested thread.      */
static void *CreateThread(void *data);

/*  -SIGUSR1 handle function.       */
static void HandleSignalUSR1(int a, siginfo_t *b, void *c);
/******************************************************************************/

/******************************************************************************/
/*                          WatchDog Functions Definition                     */
/******************************************************************************/

wd_t *MakeMeImmortal(char *path, char **argv, size_t frequency, size_t grace)
{
    wd_t *watchdog_handle = NULL;
    size_t signal_counter = 3;

    watchdog_handle = malloc(sizeof(*watchdog_handle));
    if (NULL == watchdog_handle)
    {
        perror("Malloc failed in MakeMeImmortal");

        return NULL;
    }

    watchdog_handle->path = path;


    printf("PROGRAM PID: %d \n", getpid());

    /* init environment variables */
    sprintf(temp_buffer, "%ld", frequency);
    setenv("WATCH_DOG_FREQUENCY", temp_buffer, 1);

    sprintf(temp_buffer, "%ld", grace);
    setenv("WATCH_DOG_GRACE", temp_buffer, 1);

    sprintf(temp_buffer, "%ld", signal_counter);
    setenv("WATCH_DOG_SIGNAL_COUNTER", temp_buffer, 1);

    /* if watch dog doesn't exist, first time initiation */
    if (NULL == getenv("WATCH_DOG_ISALIVE"))
    {
        switch (watchdog_handle->pid = fork())
        {
        case -1:

            perror("fork failed in MakeMeImmortal");
            free(watchdog_handle);

            return NULL;
            break;
        case 0: /* child exec */

            /* TODO: remove printf */
            if (0 > execvp(watchdog_handle->path, argv))
            {
                perror("execvp failed in MakeMeImmortal");
                free(watchdog_handle);

                return NULL;
            }
            break;
        default:
            break;
        }
    }

    else
    {
        watchdog_handle->pid = getppid(); /* if wd created program */
    }
    



    pthread_create(&watchdog_handle->pthread_id,
                   NULL,
                   &CreateThread,
                   watchdog_handle);

    return watchdog_handle;
}

void LetMeDie(wd_t *watchdog)
{
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void *CreateThread(void *data)
{
    struct sigaction sig_act = {NULL};
    /* TODO: unneeded */
    /*  char *path = NULL; */

    memset(&sig_act, '\0', sizeof(sig_act));

    /* TODO: not sure if needed. */
    /* path = ((wd_t *)data)->path; */
    sig_act.sa_sigaction = &HandleSignalUSR1;
    if (0 > sigaction(SIGUSR1, &sig_act, NULL))
    {
        perror("sigaction in watchdog.c CreateThread failed");
    }
    printf("program sending path to wd: %s \n", ((wd_t *)data)->path);
    SchedularActivate(&((wd_t *)data)->path, ((wd_t *)data)->pid);

    return NULL;
}

static void HandleSignalUSR1(int a, siginfo_t *b, void *c)
{
    (void)a;
    (void)b;
    (void)c;

    /* reset signal counter back to 3 (signals to waite until reboot)   */
    setenv("WATCH_DOG_SIGNAL_COUNTER", "3", 1);
}
/******************************************************************************/
