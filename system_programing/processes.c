#include <stdio.h>  /* printf */
#include <stdlib.h> /* system */
#include <sys/types.h>
#include <unistd.h>

/* int main()
{
    int return_value = 0;

    return_value = system(" ls -l /");
    return return_value;

    return 0;
} */

/* int main()
{
    pid_t child_pid;
    printf("the main program process ID is %d\n", (int)getpid());
    child_pid = fork();
    if (child_pid != 0)
    {
        printf("this is the parent process, with id %d\n", (int)getpid());
        printf("the child's process ID is %d\n", (int)child_pid);
    }
    else
        printf("this is the child process, with id %d\n", (int)getpid());

    return 0;
}
 */

/* Spawn a child process running a new program. 
    PROGRAM is the name of the program to run; 
        the path will be searched for this program.
    ARG_LIST is a NULL-terminated list of character strings to be 
        passed as the program's argument list. 
    Returns the process ID of the spawned process.  */ 

int spawn(char *program, char **arg_list)
{
    pid_t child_pid; /* Duplicate this process. */
    child_pid = fork();
    if (child_pid != 0) /* This is the parent process. */
        return child_pid;
    else
    {                              /* Now execute PROGRAM, searching for it in the path.  */
        execvp(program, arg_list); /* The execvp  function returns only if an error occurs.  */
        fprintf(stderr, "an error occurred in execvp\n");
        abort();
    }
}

int main()
{
    /*  The argument list to pass to the "ls" command.  */
    char *arg_list[] = {"ls", /* argv[0], the name of the program.  */ 
                        "-l", "/", NULL /* The argument list must end with a NULL.  */}; 
    /* Spawn a child process running the "ls" command. Ignore the       returned child process ID.  */
    spawn("ls", arg_list);
    printf("done with main program\n");
    return 0;
}