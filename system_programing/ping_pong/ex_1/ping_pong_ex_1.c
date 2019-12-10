/******************************************************************************/
/* Name: Ruslan Gorbaty														  */
/* Reviewer: Maor Moyal														  */
/* Group: OL767															      */
/* Description:	Implementation of exercise 1, send signals SIGUSR1 and SIGUSR2
				between parent and child.								      */
/******************************************************************************/

#define _POSIX_C_SOURCE 199309L
#include <signal.h> 	/* SIGINT 	*/
#include <sys/types.h>  /* pid_t  	*/
#include <stdio.h>		/* printf 	*/
#include <string.h> 	/* memset	*/
#include <unistd.h>		/* getpid/getppid */


/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

/* 	-refers to SIGUSR1.	*/
static sig_atomic_t pong_value = 0;

/* 	-refers to SIGUSR2.	*/
static sig_atomic_t ping_value = 0;

/* 	-sa_handler for SIGUSR1
	-set pong_value to 1 	*/
static void my_handler_1();

/* 	-sa_handler for SIGUSR2
	-set ping_value to 1 	*/
static void my_handler_2();

/* 	-Ping-Pong using fork().	*/
static void EX1();
/******************************************************************************/

int main()
{

	EX1();

	return (0);
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void my_handler_1()
{
		pong_value = 1;
}

static void my_handler_2()
{
		ping_value = 1;
}
/******************************************************************************/

/******************************************************************************/
/*                          Ping_Pong Functions Definition                    */
/******************************************************************************/

static void EX1()
{
	struct sigaction sig_action_1;
	struct sigaction sig_action_2;
	pid_t pid, p_pid;

	memset(&sig_action_1, '\0', sizeof(sig_action_1));
	memset(&sig_action_2, '\0', sizeof(sig_action_2));
	
	/* set sa_handle function to my functions */
	sig_action_1.sa_handler = &my_handler_1;
	sig_action_2.sa_handler = &my_handler_2;

	/* return value: 	
					 0 success
					-1 failure  */
	if (0 > sigaction(SIGUSR1, &sig_action_1, NULL))
	{
		perror("sigaction_1 error\n");

		return;
	}

	if (0 > sigaction(SIGUSR2, &sig_action_2, NULL))
	{
		perror("sigaction_2 error\n");
		
		return;
	}

	pid = fork();

	kill(pid, SIGUSR2); /* first signal */

	while (1)
	{
		if (0 == pid) /* son running here */
		{ 
			p_pid = getppid();

			if (1 == ping_value)
			{
				printf("%sPONG%s current process id: %d\n", SET_RED_COLOR, 
															RESET_COLOR,
															getpid());
				ping_value = 0;
				sleep(1);
				kill(p_pid, SIGUSR1);
			}
		}
		else if (pid > 0) /* parent will run here */
		{

			if (1 == pong_value)
			{
				printf("%sPING%s current process id: %d\n", SET_BLUE_COLOR,
															RESET_COLOR,
															getpid());
				pong_value = 0;
				sleep(1);
				kill(pid, SIGUSR2);
			}
		}
		else /* fork has failed */
		{
			printf("failed in fork\n");
			break;
		}
	}
}
/******************************************************************************/
