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

	return 0;
	}
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
	char usr_string[] = "10";
	
	assert(NULL != usr_string);

	switch(element->e_type)
	{
		case INT:
				element->u_type.iVar += i;
				break;

		case FLOAT:
				element->u_type.fVar += i;
				break;

		case STRING:
				element->u_type.sVar = (char *)realloc(element->u_type.sVar, strlen(element->u_type.sVar) + strlen(usr_string) + 1);

				assert(NULL != element->u_type.sVar);
				strcat(element->u_type.sVar, usr_string);
				break;

		default:
				break;
	}
}


