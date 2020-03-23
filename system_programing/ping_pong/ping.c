#define _POSIX_C_SOURCE 199309L

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include <stdio.h> /* printf */

int signal_ping = 0; 
void signal_handler1(int a, siginfo_t *b, void *c);

int main()
{
    pid_t child_pid = 0;

    struct sigaction sig = {NULL};

    sig.sa_sigaction = signal_handler1;

    sigaction(SIGUSR1, &sig, NULL);


    child_pid = fork();

    if (child_pid == 0)
    {
        execlp("pong.out", "pong.out");
    }
    
    while (1)
    {
        if (signal_ping)
        {
            printf("%d : ping\n", getpid());
            signal_ping = 0;
            kill(child_pid, SIGUSR2);
        }
    }

    return 1;
}
    
void signal_handler1(int a, siginfo_t *b, void *c)
{
    signal_ping = 1; 
}
