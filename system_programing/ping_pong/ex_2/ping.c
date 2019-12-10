/******************************************************************************/
/* Name: Ruslan Gorbaty														  */
/* Reviewer: Maor Moyal														  */
/* Group: OL767															      */
/* Description:	Implementation of exercise 2, exchange SIGUSR1 and SIGUSR2
				between processes when parent process forks and executes.     */
/******************************************************************************/

#define _POSIX_C_SOURCE 199309L
#include <signal.h>    /* SIGINT 	*/
#include <sys/types.h> /* pid_t  	*/
#include <stdio.h>     /* printf 	*/
#include <string.h>    /*	memset	*/
#include <unistd.h>    /* getpid/getppid */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

/* 	-refers to SIGUSR2.	*/
static sig_atomic_t ping_value = 0;

/* 	-sa_handler for SIGUSR2
	-set ping_value to 1 	*/
static void HandleSIGUSR2();

/* 	-Ping-Pong using fork() & exec().	*/
static void SignalPing();
/******************************************************************************/

int main()
{
    SignalPing();

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void HandleSIGUSR2()
{
    ping_value = 1;
}
/******************************************************************************/

/******************************************************************************/
/*                          Ping_Pong Functions Definition                    */
/******************************************************************************/

static void SignalPing()
{
    struct sigaction sig_action_2;
    pid_t child_pid;

    memset(&sig_action_2, '\0', sizeof(sig_action_2));

    sig_action_2.sa_handler = &HandleSIGUSR2;

    /* return value: 	
					 0 success
					-1 failure  */
    if (0 > sigaction(SIGUSR2, &sig_action_2, NULL))
    {
        perror("sigaction_2 error");

        return;
    }

    child_pid = fork();
    if(0 > child_pid)
    {
        perror("failed in fork");

        return;
    }
    else if(0 == child_pid) /* fork was successful, currently at child */
    {
        execlp("pong.out", "", NULL);
        perror("execlp failed");

        return;
    }
     
    while (1)
    {
        if (1 == ping_value)
        {
            printf("%sPING%s current process id: %d\n", SET_BLUE_COLOR,
                                                        RESET_COLOR,
                                                        getpid());
            ping_value = 0;
            sleep(1);
            kill(child_pid, SIGUSR1);
        }
    }
}
/******************************************************************************/
