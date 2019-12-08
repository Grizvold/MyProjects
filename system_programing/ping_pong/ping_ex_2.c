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
static sig_atomic_t pong_value = 0;

/* 	-sa_handler for SIGUSR2
	-set pong_value to 1 	*/
static void my_handler_2();

/* 	-Ping-Pong using fork() & exec().	*/
static void EX2();
/******************************************************************************/

int main()
{
    EX2();

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void my_handler_2()
{
    pong_value = 1;
}
/******************************************************************************/

/******************************************************************************/
/*                          Ping_Pong Functions Definition                    */
/******************************************************************************/

static void EX2()
{
    struct sigaction sig_action_2;
    pid_t child_pid;

    memset(&sig_action_2, '\0', sizeof(sig_action_2));

    /* set sa_handle function to my functions */
    sig_action_2.sa_handler = &my_handler_2;

    /* returne value: 	
					0  success
					-1 failure  */
    if (0 > sigaction(SIGUSR2, &sig_action_2, NULL))
    {
        perror("sigaction_2 error\n");

        return;
    }

    child_pid = fork();
    if(0 > child_pid)
    {
        perror("failed in fork\n");
    }
    else if(0 == child_pid) /* fork was successful, currently at child */
    {
        if(0 > execlp("pong_ex_2.out", "pong_ex_2.out"))
        {
            perror("execlp failed \n");

            return;
        }
    }

    while (1)
    {
        if (1 == pong_value)
        {
            printf("%sPING%s current process id: %d\n", SET_BLUE_COLOR,
                                                        RESET_COLOR,
                                                        getpid());
            pong_value = 0;
            sleep(1);
            kill(child_pid, SIGUSR1);
        }
    }
}
/******************************************************************************/
