#include <stdlib.h>  /* stdot */
#include <limits.h>  /* UCHAR_MAX    */
#include <stdio.h>   /* sscanf       */
#include <string.h>  /* strcspn      */

#include "vector.h"

/************************ typedefs ************************************/

typedef double(*action_func_t)(double operand1, double operand2);
typedef char* (*state_t)(vector_t *num_vec, vector_t *oper_vec, char *str);
typedef void (*paran_t)(vector_t *num_vec, vector_t *oper_vec);

typedef struct 
{
    char name;
    action_func_t func;
    int precedence;
}operator_t;

/******************************* LUTs *********************************/

static state_t compilation[UCHAR_MAX];
static operator_t operators[UCHAR_MAX];
static state_t minus[2];

/************************ forward declaration *************************/
void InitLUTs();

char* NumberState(vector_t* num_vec, vector_t* oper_vec, char *str);
char* OperatorState(vector_t* num_vec, vector_t* oper_vec, char *str);
char* MinusState(vector_t* num_vec, vector_t* oper_vec, char *str);
char* SpaceState(vector_t* num_vec, vector_t* oper_vec, char *str);
char* OpenParnState(vector_t* num_vec, vector_t* oper_vec, char *str);
char* CloseParnState(vector_t* num_vec, vector_t* oper_vec, char *str);

double Sum(double operand1, double operand2);
double Substract(double operand1, double operand2);
double Multi(double operand1, double operand2);
double Divide(double operand1, double operand2);

void Execute(vector_t* num_vec, vector_t* oper_vec);

/* 0 = Number, 1= operator */
int minus_state = 0;

/************************************************************************/

double Calculator (const char *expression, int *err)
{
    vector_t *num_vec = NULL;
    vector_t *oper_vec = NULL;
    double result =0;

    num_vec = VectorCreate(2, sizeof(double));
    if (NULL == num_vec)
    {
        *err = 1;
        return 0;
    }

    oper_vec = VectorCreate(2, sizeof(operator_t));
    if (NULL == oper_vec)
    {
        free(num_vec);
        *err = 1;
        return 0;
    }

    InitLUTs();

    /* adding a dummy to the beginning of the vector */
    VectorPushBack(oper_vec, &operators[')']);

    while ('\0' != *expression)
    {
        expression = compilation[(int)*expression](num_vec, oper_vec, (char *)expression);
    }

    while (VectorSize(oper_vec) > 1)
    {
        Execute(num_vec, oper_vec);
    }

    result = *(double *)VectorGetItemAddress(num_vec, VectorSize(num_vec)-1);

    VectorDestroy(num_vec);
    VectorDestroy(oper_vec);

    return result;
}

/************************ Internal functions *******************************/

void InitLUTs()
{
    /* compilation LUT */
    compilation['*'] = OperatorState;
    compilation['/'] = OperatorState;
    compilation['+'] = OperatorState;
    compilation['-'] = MinusState;
    compilation['('] = OpenParnState;
    compilation[')'] = CloseParnState;
    compilation['0'] = NumberState;
    compilation['1'] = NumberState;
    compilation['2'] = NumberState;
    compilation['3'] = NumberState;
    compilation['4'] = NumberState;
    compilation['5'] = NumberState;
    compilation['6'] = NumberState;
    compilation['7'] = NumberState;
    compilation['8'] = NumberState;
    compilation['9'] = NumberState;
    compilation[' '] = SpaceState;
 
    /* operators LUT */
    operators['+'].name = '+';
    operators['+'].func = Sum;
    operators['+'].precedence = 1;
    operators['-'].name = '-';
    operators['-'].func = Substract;
    operators['-'].precedence = 1;
    operators['*'].name = '*';
    operators['*'].func = Multi;
    operators['*'].precedence = 2;
    operators['/'].name = '/';
    operators['/'].func = Divide;
    operators['/'].precedence = 2;
    operators['('].name = '(';
    operators['('].precedence = 0;
    operators[')'].name = ')';
    operators[')'].precedence = 0;

    /*minus LUT*/
    minus[0] = NumberState;
    minus[1] = OperatorState;
}

char* NumberState(vector_t *num_vec, vector_t *oper_vec, char *str)
{
    double operand = 0;
   
    operand = strtod(str, &str);

    VectorPushBack(num_vec, &operand);

    /* change minus to operator mode */
    minus_state =1;

    return (char *)str;
} 


char* OperatorState(vector_t* num_vec, vector_t* oper_vec, char *str)
{
    int precedence = operators[(int)*str].precedence;
    operator_t last_operator = *(operator_t*)VectorGetItemAddress(oper_vec, VectorSize(oper_vec)-1);

    while (precedence <= last_operator.precedence)
    {
        Execute(num_vec, oper_vec);

        last_operator = *(operator_t*)VectorGetItemAddress(oper_vec, VectorSize(oper_vec)-1);
    }

    VectorPushBack(oper_vec, &operators[(int)*str]);

    /* change minus to number mode */
    minus_state = 0;

    return (char *)str+1;
}

char* SpaceState(vector_t *num_vec, vector_t *oper_vec, char *str)
{
    return (char *)str+1;
}

char* MinusState(vector_t *num_vec, vector_t *oper_vec, char *str)
{
    return minus[minus_state](num_vec, oper_vec, (char *)str);
}

char* OpenParnState(vector_t* num_vec, vector_t* oper_vec, char *str)
{
    VectorPushBack(oper_vec, &operators[(int)'(']);

     return (char *)str+1;
}

char* CloseParnState(vector_t* num_vec, vector_t* oper_vec, char *str)
{
    while (((operator_t*)VectorGetItemAddress(oper_vec, VectorSize(oper_vec)-1))->name != '(')
    {
        Execute(num_vec, oper_vec);
    }

    VectorPopBack(oper_vec);

    return (char *)str+1;
}

void Execute(vector_t *num_vec, vector_t *oper_vec)
{
    operator_t operator;
    double operand1 =0;
    double operand2 =0;
    double result = 0;

    operator = *(operator_t *)VectorGetItemAddress(oper_vec, VectorSize(oper_vec)-1);
    operand2 = *(double *)VectorGetItemAddress(num_vec, VectorSize(num_vec)-1);
    operand1 = *(double *)VectorGetItemAddress(num_vec, VectorSize(num_vec)-2);

    VectorPopBack(oper_vec);
    VectorPopBack(num_vec);
    VectorPopBack(num_vec);

    result = operators[(int)operator.name].func(operand1, operand2);
    VectorPushBack(num_vec, &result);
}

double Sum(double operand1, double operand2)
{
    return operand1 + operand2;
}

double Substract(double operand1, double operand2)
{
    return operand1 - operand2;  
}

double Multi(double operand1, double operand2)
{
    return operand1 * operand2;
}

double Divide(double operand1, double operand2)
{
   return operand1 / operand2;
}


