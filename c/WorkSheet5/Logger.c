#include <stdio.h> /* fopen */
#include <string.h> /* strlen/strncmp */
#include <stdlib.h> /* malloc */

#define OPTION_COUNT 5
#define MAX_USER_INPUT 100
#define UNUSED (void)

/********************** typedefs and enum **********************/
/* create enum for status to return from function */
enum status{success, failure};

/* typedef to status enum */ 
typedef enum status status_t;

/* function pointer to proper operator	*/
/* and type def to this pointer		*/
typedef status_t (*Action_t)(const char *, const char *);

/* creating struct with string (probably operation)	*/
/* and proper function to this string			*/ 
typedef struct operation
{
	char *option;
	Action_t action;
}operation_t;
/***************************************************************/

/********************** func declaration ***********************/
status_t RemoveOperation(const char *filename,const  char *usr_str);
status_t CountOperation(const char *filename,const  char *usr_str);
status_t ExitOperation(const char *filename,const  char *usr_str);
status_t AppendOperation(const char *filename,const  char *usr_str);
status_t WriteToStartOperation(const char *filename,const  char *usr_str);
int ParserForInput(const char *usr_str, operation_t *);
/***************************************************************/


/***** append usr_string to end of file *****/
status_t AppendOperation(const char *filename,const char *usr_str)
{
	FILE *file_p = NULL;

	file_p = fopen(filename, "a+"); 
	if(NULL == file_p)
	{
		printf("\n\nFailed to open %s\n\n", filename);
		return failure;
	}

	fprintf(file_p, "%s", usr_str);
	printf("\n\nAppendation was  successful\n\n");

	if(0 != fclose(file_p))
	{
		printf("\n\nFailed to close %s\n\n", filename);
		return failure;
	}	

	return success;
}

/***** write string to start of file *****/
status_t WriteToStartOperation(const char *filename,const char *usr_str)
{
	FILE *file_p = NULL;
	FILE *temp_p = NULL;
	char *buffer = NULL;
	char *temp_file = "temp.txt";
	size_t size_of_buffer = 1000;
	size_t size_of_copied_data = 0;


	buffer = (char *)malloc(sizeof(char) * size_of_buffer);
	if(NULL == buffer)
	{
		printf("\n\nFailed to allocate memory for the buffer by using malloc\n\n");				
		return failure;
	}

	
	/*------------- open files and confirm success -------------*/
	file_p = fopen(filename, "r");
	if(NULL == file_p)
	{
		printf("\n\nFailed to open %s\n\n", filename);
		return failure;
	}

	temp_p = fopen(temp_file, "a");
	if(NULL == temp_p)
	{
		printf("\n\nFailed to open %s\n\n", temp_file);
		return failure;
	}
	/*----------------------------------------------------------*/

	/****** Write usr_string to first line of our temp_file ******/
	fprintf(temp_p, "%s", ++usr_str);

	/*=========== Copy rest of old file to new file ===========*/
	do
	{
		size_of_copied_data = fread(buffer, 1, size_of_buffer, file_p);
		fwrite(buffer, 1, size_of_copied_data, temp_p);
	}
	while(size_of_copied_data == size_of_buffer);
	/*=========================================================*/

	/*===== closing both file =====*/ 

	if(0 != fclose(file_p))
	{
		printf("\n\n Failed to close %s\n\n", filename);
		return failure;
	}

	if(0 != fclose(temp_p))
	{
		printf("\n\nFailed to close %s\n\n", filename);
		return failure;
	}		
	/*=============================*/ 

	/*=========== deleting original file ===========*/
	if(0 == remove(filename))
	{
		printf("\n\nDeleted original file successfully\n\n");
	}

	else
	{
		printf("\n\nFailed to delete the original file\n\n");
		return failure;
	}
	/*==========================================*/
	
	/*=========== renaming temp file to old file name ===========*/
	if(0 == rename(temp_file, filename))
	{
		printf("\n\nRenaming temp file was successfull\n\n");
	}

	else
	{
		printf("\n\nFailed to rename the temp file\n\n");
		return failure;
	}
	/*===========================================================*/
	
	printf("\n\nAppendoperator success\n\n");

	free(buffer);

	return success;
}

/***** exit program *****/
status_t ExitOperation(const char *filename,const char *usr_str)
{
	UNUSED filename;
	UNUSED usr_str;

	printf("\n\nExiting program\n\n");

	return failure;
}

/***** counting lines in file *****/
status_t CountOperation(const char *filename,const char *usr_str)
{
	FILE *file_p = NULL;
	char char_from_file = 0;
	int line_counter = 0;
	UNUSED usr_str;
	

	file_p = fopen(filename, "r");
	if(NULL == file_p)
	{
		printf("\n\nFailed to open %s\n\n", filename);
	}



	while(EOF != char_from_file)
	{
		char_from_file = getc(file_p);
			if(char_from_file == '\n')
			{
				line_counter++;
			}
	}

	if(0 != fclose(file_p))
	{
		printf("\n\nFailed to close %s\n\n", filename);
	}	

	printf("\n\nThe number of lines in current file is: %d.\n\n", line_counter);

	return success;
}

/***** remove file *****/
status_t RemoveOperation(const char *filename,const  char *usr_str)
{
	UNUSED usr_str;

	if(0 == remove(filename))
	{
		printf("\n\nDeleted successfully  \n\n");
		return success; 
	}
	
	else
	{
		printf("\n\nFailed to delete the file  \n\n");
		return failure;
	}
}

/***** parser for user input string *****/
int ParserForInput(const char *usr_input, operation_t *strct_ptr)
{
	int action_num = 0;
	size_t len_of_input = 0;
	size_t len_of_operation = 0;

	switch (*usr_input)
	{
		case '-':
			/* one of "-" options (remove/exit/count) */
			/* if none of the options action_num = 3  */
			/* which is "append" function in struct   */
			len_of_input = strlen(usr_input);
	
			for(action_num = 0; action_num < 3; action_num++)
			{
				/* because of fgets we compare to strlen + 1 (adds \n) */
				len_of_operation = strlen(strct_ptr[action_num].option);				
				
				if(len_of_input == (len_of_operation + 1))	
				{
					if(strncmp(usr_input, strct_ptr[action_num].option, len_of_operation) == 0)
					{
						break;
					}					
				}
			}

			break;
		case '<':
			action_num = 4;

			break;
		default:
			action_num = 3;

			break;
	}

	return action_num;
}

int main(int argc, char **argv)
{	
	/******* Data declaration and initialization *******/
	operation_t logger_operations[OPTION_COUNT];
	char *file_name = argv[1];
	char usr_string[MAX_USER_INPUT] = {0};
	int operation_num = 0;
	status_t program_stat = success;
	UNUSED argc;

	/*======= struct of functions =======*/
	logger_operations[0].option = "-remove";
	logger_operations[0].action = RemoveOperation;

	logger_operations[1].option = "-count";
	logger_operations[1].action = CountOperation;

	logger_operations[2].option = "-exit";
	logger_operations[2].action = ExitOperation;

	logger_operations[3].option = "";
	logger_operations[3].action = AppendOperation;

	logger_operations[4].option = "<";
	logger_operations[4].action = WriteToStartOperation;
	/*===================================*/

	/*-------------------- operation options -------------------*/
	printf("%*c Worksheet5 Files Menu:\n", 5, ' ');
 	printf("%*c 1. -remove the file\n", 5, ' ');
	printf("%*c 2. -exit exit program\n", 5, ' ');
 	printf("%*c 3. -count lines in file\n", 5, ' ');
	printf("%*c 4. < move string input to start of file\n", 5, ' ');
	printf("%*c 5. anyother option - append string to the end of file\n\n\n", 5, ' ');
	/*----------------------------------------------------------*/

	/*======= while -exit wasnt typed =======*/
	while(program_stat != failure)
	{
	fgets(usr_string, MAX_USER_INPUT, stdin);
	operation_num = ParserForInput(usr_string, logger_operations);

	program_stat = logger_operations[operation_num].action(file_name, usr_string);	
	}	
	/*=======================================*/
	
	return 0;
}

