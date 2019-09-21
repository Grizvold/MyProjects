#include "Polymorphism.h"
#include <stdlib.h> /* malloc/free */
#include <stdio.h> /* prinft */
#include <string.h> /* strcpy/strcat/strlen */
#include <assert.h> /* assert */

void *GetVal(const data_s_t *element)
{
	switch(element->e_type)
	{
		case INT:
				return (void *)&element->u_type.iVar;
				break;

		case FLOAT:
				return (void *)&element->u_type.fVar;
				break;

		case STRING:
				return (void *)element->u_type.sVar;
				break;

		default:
				break;

	}

	return 0;
}

void SetVal(data_s_t *element, data_e_t var_type, const void *val)
{
	char *temp = NULL;

	element->e_type = var_type;

	assert (NULL != val);

	switch(var_type)
	{
		case INT:
				element->u_type.iVar = *((int *) val); 
				break;

		case FLOAT:
				element->u_type.fVar = *((float *) val);
				break;

		case STRING:
				temp = (char *)malloc((strlen(val) + 1) * sizeof(char));
				if(NULL == temp)
				{
					return;
				}
	
				element->u_type.sVar = temp;
				strcpy(element->u_type.sVar, (char *) val);
				break;

		default:
				break;
	}
}

void PrintVal(const data_s_t *element)
{
	switch(element->e_type)
	{
		case INT:
				printf("\ntype: int, value: %d\n", element->u_type.iVar);
				break;

		case FLOAT:
				printf("\ntype: float, value: %f\n", element->u_type.fVar);
				break;

		case STRING:
				printf("\ntype: string, value: %s\n", element->u_type.sVar);
				break;

		default:
				break;
	}
}

void AddVal(data_s_t *element, int i)
{
	char *usr_string = NULL;
	

	switch(element->e_type)
	{
		case INT:
				element->u_type.iVar += i;
				break;

		case FLOAT:
				element->u_type.fVar += i;
				break;

		case STRING:
				assert (0 != i);
				assert (NULL != element->u_type.sVar);
				
				usr_string = (char *)malloc(INPUT_NUM_LENGTH);
				if (NULL == usr_string)
				{
					return;
				}

				sprintf(usr_string, "%d", i);
				
				element->u_type.sVar = (char *)realloc(element->u_type.sVar, strlen(element->u_type.sVar) + strlen(usr_string) + 1);

				assert(NULL != element->u_type.sVar);
				strcat(element->u_type.sVar, usr_string);

				free(usr_string);
				usr_string = NULL;
				break;

		default:
				break;
	}
}

void ClearStringElement(data_s_t *element)
{
	if (STRING == element->e_type)
	{
		free(element->u_type.sVar);
		element->u_type.sVar = NULL;
		printf("\nsuccessfully freed string element\n");		
	}
}

