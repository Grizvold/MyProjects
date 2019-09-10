#include <stdio.h> /* fopen */
#include <string.h> /* strlen/strncmp */

#define OPTION_COUNT 5
#define MAX_USER_INPUT 100

/* unused variables */
typedef void UNUSED_t;

/* create enum for status to return from function */
enum status{success, failure};

/* typedef to status enum */ 
typedef enum status status_t;

/* function pointer to proper operator	*/
/* and type def to this pointer		*/
typedef status_t (*Action_t)(const char *, const char *);

/* creating struct with string (probably operation)	*/
/* and proper function to this string			*/ 
struct operation
{
	char *option;
	Action_t action;
}operation[OPTION_COUNT];

typedef struct operation operation_t;

status_t RemoveOperation(const char *filename,const  char *usr_str);
status_t CountOperation(const char *filename,const  char *usr_str);
status_t ExitOperation(const char *filename,const  char *usr_str);
status_t AppendOperation(const char *filename,const  char *usr_str);
status_t WriteToStartOperation(const char *filename,const  char *usr_str);
int ParserForInput(const char *usr_str);

status_t AppendOperation(const char *filename,const char *usr_str)
{
	FILE *file_p = fopen(filename, "a+"); 
	fprintf(file_p, usr_str);
	printf("\nappendoperator success\n");
	return success;
}

status_t WriteToStartOperation(const char *filename,const char *usr_str)
{
	printf("\nappendoperator success\n");
	return success;
}


status_t ExitOperation(const char *filename,const char *usr_str)
{
	printf("\nexitoperator success\n");
	return success;
}

status_t CountOperation(const char *filename,const char *usr_str)
{
	printf("\ncountoperator success\n");
	return success;
}

status_t RemoveOperation(const char *filename,const  char *usr_str)
{
	printf("\nremoveoperator success\n");
	return success;
}

/* parser for user input string */
int ParserForInput(const char *usr_input)
{
	int action_num = 0;

	switch (*usr_input)
	{
		case '-':
			
			break;
		case '<':
			break;
		default:
			action_num = 4;
			break;
	}

	printf("\n%d\n", action_num);
	return action_num;
}

int main(int argc, char **argv)
{	
	operation_t logger_operations[OPTION_COUNT];
	/* file name from user */
	char *file_name = argv[1];
	char usr_string[MAX_USER_INPUT] = {0};
	int operation_num = 0;

	/* struct of functions  */
	logger_operations[0].option = "-remove";
	logger_operations[0].action = RemoveOperation;

	logger_operations[1].option = "-count";
	logger_operations[1].action = CountOperation;

	logger_operations[2].option = "-exit";
	logger_operations[2].action = ExitOperation;

	logger_operations[3].option = "<";
	logger_operations[3].action = WriteToStartOperation;

	logger_operations[4].option = "";
	logger_operations[4].action = AppendOperation;

/******************* my while **********************************/ 
	fgets(usr_string, MAX_USER_INPUT, stdin);
	operation_num = ParserForInput(usr_string);

	logger_operations[operation_num].action(file_name, usr_string);		
/****************************************************************/	
	return 0;
}

