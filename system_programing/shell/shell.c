#include <stdio.h>      /* printf,scanf */
#include <stdlib.h>     /* system       */
#include <sys/types.h>  /* pid_t        */
#include <unistd.h>     /* fork         */
#include <sys/wait.h>   /* wait         */
#include <string.h>     /* strcmp       */


/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *RESET_COLOR = "\033[0m";

/* -Run process by <system> implementation. */
static void ShellBySystem();

/* -Run process by <fork> and <exec>. */
static void ShellByForkExec();

/* -*/
static void ShellParser(char *cmnd_str, char **argv);

/******************************************************************************/


int main()
{   
    char input_char = 0;

    while (1)
    {
        printf("\n%sChoose execution: %s", SET_BLUE_COLOR, RESET_COLOR);
        printf("\n\t%s1%s for <system>", SET_RED_COLOR, RESET_COLOR);
        printf("\n\t%s2%s for <fork & exec>", SET_RED_COLOR, RESET_COLOR);
        printf("\n\t%s0%s to exit\n", SET_RED_COLOR, RESET_COLOR);

        input_char = getchar();
        
        switch (input_char)
        {
            case '1':
                    ShellBySystem();
                    break;

            case '2':
                    ShellByForkExec();
                    break;
            default:
                    break;
        }

        if('0' == input_char)
        {
            break;
        }
        
    }
    
    return 0;
}

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/

static void ShellBySystem()
{
    int return_value = 0;
    char *fgets_status = "0"; /* return value of fgets */
    char *input_line = NULL;
    size_t line_leng = 80; /* input line limit */

    input_line = (char *)malloc(sizeof(char) * line_leng);

    printf("\n\t%sEnter your command:%s\n", SET_BLUE_COLOR, RESET_COLOR);

    /* while fgets doesnt fail && <exit> wasnt pressed && */
    while(NULL != fgets_status && 0 != strcmp("exit\n", input_line))
    {
        fgets_status = fgets(input_line, line_leng, stdin);
        return_value = system(input_line);
        printf("Return value of system: %s%d%s \n\n", SET_RED_COLOR, 
                                                        return_value,  
                                                        RESET_COLOR);
    }
}

static void ShellByForkExec()
{
    pid_t process_id = 0;
    char **args = NULL;
    int execvp_return_value = 0;
    char line_command[50] = "\0";
    size_t number_of_arguments = 50;
    char *fgets_return_status = "\0";
    int wait_status = 0;

    args = (char **)malloc(sizeof(*args) * number_of_arguments);
    if(NULL == args)
    {
        perror("Malloc failed in ShellByForkExec\n");
    
        return;
    }

    /* as long as "exit" wasnt pressed */
    while(NULL != fgets_return_status && 0 != strcmp(line_command, "exit"))
    {
        fgets_return_status = fgets(line_command, 50, stdin);
        /* start parsing by delimiters */
        ShellParser(line_command, args);

        process_id = fork();
        if (0 > process_id)
        {
            perror("Error in forking \n");
            break;
        }
        /* if process id = 0 -> we are at child process */
        else if (0 == process_id)
        {
            execvp_return_value = execvp(*args, args);
            if(0 > execvp_return_value)
            {
                perror("execvp failed in ShellByForkExec\n");                
            }
            /* waite untill wait return process id child  */
            while (wait(&wait_status) != process_id)
            {}    
        }
    }

    free(args);
    args = NULL;    
}

static void ShellParser(char *command_string, char **argv)
{
    size_t i = 0;
    char delimiter[3] = "\0"; /* space/new_line/end_line */

    delimiter[0] = ' '; 
    delimiter[1] = '\n';

    argv[0] = strtok(command_string, delimiter);

    while (NULL != argv[i])
    {
        ++i;
        argv[i] = strtok(NULL, delimiter);
    }    
}
/******************************************************************************/


