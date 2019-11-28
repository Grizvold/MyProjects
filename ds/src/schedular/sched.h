#ifndef __SCHED_H__
#define __SCHED_H__

#include <stddef.h> /* size_t */

#include "uid.h"

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
typedef struct sched sched_t;

typedef int (*operation_func_t)(void *param);
/******************************************************************************/

/******************************************************************************/
/*                          Schedule Functions Declaration                    */
/******************************************************************************/
/*	-Creates empty schedular.
	-Returns pointer to schedular.	*/
sched_t *SchedCreate();

/* 	-Adds a task to the schedular.(Requested UID of task).
	-Returns:
		1 if task needs to run continuously.
		0 if not.	*/
ilrd_uid_t SchedAddTask(sched_t *sched, size_t interval_sec,
				   		operation_func_t act_func, void *param);

/*	-Removes task with requested UID from schedular.	*/
void SchedRemoveTask(sched_t *sched, ilrd_uid_t uid);

/*	-Start running schedular.	*/
void SchedRun(sched_t *sched);

/*	-Stop running schedular.	*/
void SchedStop(sched_t *sched);

/*	-Destroys requested schedular and frees memory.	*/
void SchedDestroy(sched_t *sched);
/******************************************************************************/
#endif /* __SCHED_H__ */