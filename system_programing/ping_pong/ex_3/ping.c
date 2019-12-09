#define _POSIX_C_SOURCE 199309L
#include <signal.h> 	/* SIGINT 	*/
#include <sys/types.h>  /* pid_t  	*/
#include <stdio.h>		/* printf 	*/
#include <string.h> 	/*	memset	*/
#include <unistd.h>		/* getpid/getppid */

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

/* 	-refers to SIGUSR1.	*/
static sig_atomic_t ping_value = 0;
static pid_t pong_pid = 0;

/* 	-sa_handler for SIGUSR2
	-set ping_value to 1 	*/
static void HandleSIGUSR1(int , siginfo_t *, void *);

/******************************************************************************/

int main()
{
    struct sigaction sig_action1;

    sig_action1.sa_sigaction = &HandleSIGUSR1;
    sig_action1.sa_flags = SA_SIGINFO;

    if(0 > sigaction(SIGUSR1, &sig_action1, NULL))
    {
        perror("sigaction_1 error");

        return 1;
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
            kill(pong_pid, SIGUSR2);
        }
    }

    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

void HandleSIGUSR1(int a, siginfo_t *info, void *c)
{
    (void)a;
    (void)c;

    pong_pid = info->si_pid;
    ping_value = 1; 
}
/******************************************************************************/
