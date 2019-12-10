/******************************************************************************/
/* Name: Ruslan Gorbaty														  */
/* Reviewer: Maor Moyal														  */
/* Group: OL767															      */
/* Description:	Implementation of exercise 3, exchange SIGUSR1 and SIGUSR2
				between processes.                                            */
/******************************************************************************/

#define _POSIX_C_SOURCE 199309L
#include <signal.h> 	/* SIGINT 	*/
#include <sys/types.h>  /* pid_t  	*/
#include <stdio.h>		/* printf 	*/
#include <string.h> 	/*	memset	*/
#include <stdlib.h>     /* atoi     */
#include <unistd.h>		/* getpid/getppid */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *RESET_COLOR = "\033[0m";

/* 	-refers to SIGUSR1.	*/
static sig_atomic_t pong_value = 0;

/* 	-sa_handler for SIGUSR2
	-set pong_value to 1 	*/
static void HandleSIGUSR2(int , siginfo_t *, void *);
/******************************************************************************/

int main(int argc, char **argv)
{
    pid_t ping_pid = 0;

    struct sigaction sig_action2;

    sig_action2.sa_sigaction = &HandleSIGUSR2;
    sig_action2.sa_flags = SA_SIGINFO;
    (void)argc;

    ping_pid = atoi(argv[1]);
    
    if(0 > sigaction(SIGUSR2, &sig_action2, NULL))
    {
        perror("sigaction_2 error");

        return 1;
    }

    kill(ping_pid, SIGUSR1);

    while (1)
    {
        if (1 == pong_value)
        {
            printf("%sPONG%s current process id: %d\n", SET_RED_COLOR,
                                                        RESET_COLOR,
                                                        getpid());
            pong_value = 0 ;
            sleep(1);
            kill(ping_pid, SIGUSR1);
        }
    }

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

void HandleSIGUSR2(int a, siginfo_t *b, void *c)
{
    (void)a;
    (void)b;
    (void)c;

    pong_value = 1;
}
/******************************************************************************/
