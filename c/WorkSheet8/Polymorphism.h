#ifndef __POLYMORPHISM_H__
#define __POLYMORPHISM_H__

/************************** typedefs ***************************/
#define INPUT_NUM_LENGTH 20

typedef enum{INT, FLOAT, STRING}data_e_t;

typedef union
{
	int iVar;
	float fVar;
	char *sVar;
}data_u_var;

typedef struct 
{
	data_e_t e_type;
	data_u_var u_type;
}data_s_t;
/***************************************************************/

/********************** func declaration ***********************/

void *GetVal(const data_s_t *element);

void SetVal(data_s_t *element, data_e_t, const void *val);

void PrintVal(const data_s_t *element);

void AddVal(data_s_t *element, int i);

void ClearStringElement(data_s_t *element);
/***************************************************************/

#endif

/*
typedef struct 
{
	typedef enum{INT, FLOAT, STRING}data_e_t;
	typedef union
	{
		int iVar;
		float fVar;
		char *sVar;
	}data_u_var;
}data_s_t;
*/
