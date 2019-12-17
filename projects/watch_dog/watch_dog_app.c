/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Sigal Galker                                                     */
/* Group: OL767                                                               */
/* Description: WatchDog implementation.                                      */
/******************************************************************************/


#define _POSIX_C_SOURCE 200112L /* required for sigaction/env variable */
#include <stddef.h>             /* size_t   */
#include <pthread.h>            /* pthread_create */
#include <unistd.h>             /* fork     */
#include <signal.h>             /* sigaction */
#include <stdlib.h>             /* malloc, setenv   */
#include <stdio.h>              /* perror   */
#include <sys/types.h>
#include <string.h>   /* sleep  */

#include "signal_manager.h" 

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

/*  -SIGUSR1 handle function.       */
static void HandleSignalUSR1(int a, siginfo_t *b, void *c);
/******************************************************************************/

int main(int argc, char **argv)
{
    struct sigaction sig_act = {NULL};
    (void)argc;
    
    sig_act.sa_sigaction = &HandleSignalUSR1;
    if (0 > sigaction(SIGUSR1, &sig_act, NULL))
    {
        perror("sigaction in watchdog.c CreateThread failed\n");

        return 1;
    }

    SchedularActivate(argv, *(int *)getenv("WATCH_DOG_PARENT_PID"));

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void HandleSignalUSR1(int a, siginfo_t *b, void *c)
{
    (void)a;
    (void)b;
    (void)c;

    /* reset signal counter back to 3 (signals to waite until reboot)   */
    setenv("WATCH_DOG_SIGNAL_COUNTER", "3", 1);
}
/******************************************************************************/
