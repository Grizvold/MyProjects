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

/* 	-refers to SIGUSR2.	*/
static int ping_value = 0;

/* 	-sa_handler for SIGUSR1
	-set pong_value to 1 	*/
void my_handler_1();

/* 	-Ping-Pong using fork().	*/
void EX2();
/******************************************************************************/

int main()
{
    EX2();

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

void my_handler_1()
{
	ping_value = 1;
}

/******************************************************************************/

/******************************************************************************/
/*                          Ping_Pong Functions Definition                    */
/******************************************************************************/

void EX2()
{
	struct sigaction sig_action_1;
	pid_t parent_pid;

	memset(&sig_action_1, '\0', sizeof(sig_action_1));
	
	/* set sa_handle function to my functions */
	sig_action_1.sa_handler = &my_handler_1;

	/* returne value: 	
					0  success
					-1 failure  */
	if (0 > sigaction(SIGUSR1, &sig_action_1, NULL))
	{
		perror("sigaction_1 error\n");

		return;
	}

    parent_pid = getppid();
    kill(parent_pid, SIGUSR2);

	while (1)
	{
        if(1 == ping_value)
        {
            printf("%sPONG%s current process id: %d\n", SET_RED_COLOR,
                                                        RESET_COLOR,
                                                        getpid());
            ping_value = 0;
            sleep(1);
            parent_pid = getppid();
            kill(parent_pid, SIGUSR2);
        }
	}
}
/******************************************************************************/
