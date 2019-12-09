#define _POSIX_C_SOURCE 199309L
#include <signal.h> 	/* SIGINT 	*/
#include <sys/types.h>  /* pid_t  	*/
#include <stdio.h>		/* printf 	*/
#include <string.h> 	/*	memset	*/
#include <unistd.h>		/* getpid/getppid */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *RESET_COLOR = "\033[0m";

/* 	-refers to SIGUSR1.	*/
static sig_atomic_t pong_value = 0;

/* 	-sa_handler for SIGUSR1
	-set pong_value to 1 	*/
static void HandleSIGUSR1();

/* 	-Ping-Pong using fork().	*/
static void SignalPong();
/******************************************************************************/

int main()
{
    SignalPong();

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void HandleSIGUSR1()
{
	pong_value = 1;
}

/******************************************************************************/

/******************************************************************************/
/*                          Ping_Pong Functions Definition                    */
/******************************************************************************/

static void SignalPong()
{
	struct sigaction sig_action_1;

	memset(&sig_action_1, '\0', sizeof(sig_action_1));
	
	sig_action_1.sa_handler = &HandleSIGUSR1;

	/* returne value: 	
					0  success
					-1 failure  */
	if (0 > sigaction(SIGUSR1, &sig_action_1, NULL))
	{
		perror("sigaction_1 error");

		return;
	}

	/* init signal to parent */
	kill(getppid(), SIGUSR2);

	while (1)
	{
        if(1 == pong_value)
        {
            printf("%sPONG%s current process id: %d\n", SET_RED_COLOR,
                                                        RESET_COLOR,
                                                        getpid());
            pong_value = 0;
            sleep(1);
            kill(getppid(), SIGUSR2);
        }
	}
}
/******************************************************************************/
