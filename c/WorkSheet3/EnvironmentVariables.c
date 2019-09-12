#include <stdio.h> /* printf */
#include <string.h> /* strcpy, strlen */
#include <ctype.h> /* tolower */
#include <stdlib.h> /* malloc */

void ToLower(char *); /* convert substring to lowercase */
char *SubStringAllocation(char *); /* allocate dynamic mamory to the substrings */

/* convert string to lower case string using func tolower */
void ToLower(char *usr_string)
{
	while('\0' != *usr_string)
	{
		*usr_string = tolower(*usr_string);
		usr_string++;
	}
}

/* allocate dynamic memory to subarrays of env elements */
char *SubStringAllocation(char *env_subelement)
{
	size_t str_size = strlen(env_subelement);
	
	/* add NULL at end */
	str_size++;

	if(NULL == env_subelement)
	{
		return NULL;
	}
	else
	{
		return (char*)malloc(sizeof(char) * str_size);
	}
}

int main(int argc, char* argv[], char* envp[])
{
	size_t envp_itr = 0, buffer_itr = 0;
	char **buffer = NULL;
	
	/* getting size of the env variables */
	while(NULL != envp[envp_itr])
	{	
		envp_itr++;
	}

	/* create buffer of size evnp+itr + 1 (for NULL)*/
	buffer = (char **)malloc(sizeof(char*) * (envp_itr + 1));
	
	envp_itr = 0;
	/* allocate memory to every substring of env.element */
	while(NULL != envp[envp_itr])
	{	
		buffer[buffer_itr] = SubStringAllocation(envp[envp_itr]);
		strcpy(buffer[buffer_itr], envp[envp_itr]);
		ToLower(buffer[buffer_itr]);
		buffer_itr++; 
		envp_itr++;
	}


	/* put NULL at the end of buffer */
	buffer[buffer_itr] = NULL;

	buffer_itr = 0;
	/* test print of buffer */
	while(NULL != buffer[buffer_itr])
	{
		printf("\n%s", buffer[buffer_itr]);
		buffer_itr++;
	}
	
	/* free alocated memory to substrings */ 
	buffer_itr = 0;
	while(NULL != buffer[buffer_itr])
	{
		free(buffer[buffer_itr]);
		buffer_itr++;
	}

	/* free buffer itself */
	free(buffer);
	buffer = NULL;

	return 0;
}
