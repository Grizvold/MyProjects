#include <time.h>
#include <stdio.h>		
#include <stdlib.h>  /* malloc */
#include <string.h> /*strlen */

#include "sched.h"

int FuncMsg(void *param);
int FuncStop(void *param);
int FuncAdd(void *param);
int FuncRemove(void *param);

typedef struct data
{
	char *msg;
	ilrd_uid_t uid;
	sched_t *sched;
} data_t;

int main()
{
	sched_t *sched = SchedCreate();

	data_t *array = NULL;
	array = malloc(sizeof(*array) * 5);
	if (NULL == array)
	{
		return 1;
	}

	array[0].msg = "hello-world";
	array[0].sched = sched;
	array[1].msg = "bye";
	array[1].sched = sched;
	array[2].msg = "msg_2";
	array[2].sched = sched;
	array[3].msg = "msg_1";
	array[3].sched = sched;
	array[4].msg = "world";
	array[4].sched = sched;

	array[0].uid = SchedAddTask(sched, 2, FuncMsg, &array[0]);
	array[1].uid = SchedAddTask(sched, 4, FuncMsg, &array[1]);
	array[2].uid = SchedAddTask(sched, 10, FuncAdd, &array[3]);
	array[4].uid = SchedAddTask(sched, 16, FuncRemove, &array[0]);

	SchedAddTask(sched, 25, FuncStop, sched);

	SchedRun(sched);
	/*	SchedRun(sched);*/

	SchedDestroy(sched);

	free(array);
	array = NULL;

	return 0;
}

int FuncMsg(void *param)
{
	printf("%s\n", ((data_t *)param)->msg);

	if (strlen(((data_t *)param)->msg) <= 4)
	{
		return 0;
	}

	return 1;
}

int FuncStop(void *param)
{
	SchedStop((sched_t *)param);

	return 1;
}

int FuncAdd(void *param)
{
	((data_t *)param)->uid = SchedAddTask(((data_t *)param)->sched, 3, FuncMsg, (data_t *)param);

	return 0;
}

int FuncRemove(void *param)
{
	SchedRemoveTask(((data_t *)param)->sched, ((data_t *)param)->uid);

	return 0;
}