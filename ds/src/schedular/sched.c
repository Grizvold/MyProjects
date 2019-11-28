#include <stddef.h> /* size_t 		*/
#include <stdio.h>  /* perror 		*/
#include <stdlib.h> /* malloc, free	*/
#include <assert.h> /* assert		*/
#include <unistd.h> /* sleep		*/

#include "task.h"	/* */
#include "time.h"	/* */
#include "sched.h"   /* API			*/
#include "uid.h"	 /* ilrd_uid_t	*/
#include "pq_heap.h" /*  */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
struct sched
{
	pq_t *p_queue;
	int status; /* 	0 - to stop
				 	1 - to continue running.	*/
};

typedef enum
{
	SUCCESS = 0,
	FAILURE
} status_t;
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/
/* 	-Returns if data_2 < data_1 */
static int SchedHelperIsBefore(const void *data_1, const void *data_2, void *param);
/* 	-Search requested task uid	*/
static int SchedHelperIsMatch(const void *data, const void *param);
/******************************************************************************/

/******************************************************************************/
/*                          Schedule Component Definition                     */
/******************************************************************************/
sched_t *SchedCreate()
{
	sched_t *new_sched = NULL;

	while (1)
	{
		new_sched = (sched_t *)malloc(sizeof(*new_sched));
		if (NULL == new_sched)
		{
			perror("Malloc in SchedCreate failed");
			break;
		}

		new_sched->p_queue = PQCreate(&SchedHelperIsBefore, NULL);
		if (NULL == new_sched->p_queue)
		{
			perror("Malloc in SchedCreate in PQCreate failed");
			break;
		}

		new_sched->status = 0;

		return new_sched;
	}

	free(new_sched);
	new_sched = NULL;

	return NULL;
}

void SchedDestroy(sched_t *sched)
{
	task_t *task = NULL;

	assert(NULL != sched);

	for (; !PQIsEmpty(sched->p_queue);)
	{
		task = PQDequeue(sched->p_queue);
		free(task);
		task = NULL;
	}

	PQDestroy(sched->p_queue);
	sched->p_queue = NULL;

	free(sched);
	sched = NULL;
}

void SchedRun(sched_t *sched)
{
	task_t *curr_task = NULL;
	time_t time_to_next_task = 0;
	int is_continue_running = 0;

	assert(NULL != sched);

	/* init sched status to start the run */
	for (sched->status = 1; 1 == sched->status;)
	{
		curr_task = PQPeek(sched->p_queue);
		time_to_next_task = curr_task->next_run_time;

		/* sleep time untill next task */
		sleep(TimeDiff(time_to_next_task, TimeCurrTime()));

		curr_task = PQDequeue(sched->p_queue);
		is_continue_running = TaskRun(curr_task);

		/* To keep running the current task:
				update next_run_time and put back into PQ */
		if(is_continue_running)
		{
			curr_task->next_run_time = 	curr_task->interval_time + TimeCurrTime();
			PQEnqueue(sched->p_queue, curr_task);
		}
		/* To stop running the current task: free current task.	*/
		else
		{
			free(curr_task);
			curr_task = NULL;
		}
	}
}

void SchedStop(sched_t *sched)
{
	assert(NULL != sched);

	sched->status = 0;
}

ilrd_uid_t SchedAddTask(sched_t *sched, size_t interval_sec,
						operation_func_t act_func, void *param)
{
	task_t *task = TaskCreate(interval_sec, act_func, param);
	ilrd_uid_t error_uid = {0};

	assert(NULL != sched);

	while (1)
	{
		if (NULL == task)
		{
			break;
		}

		if (FAILURE == PQEnqueue(sched->p_queue, task))
		{
			break;
		}

		return task->uid;
	}

	free(task);
	task = NULL;

	error_uid = UIDCreate();
	error_uid.is_error = 1;

	return error_uid;
}

void SchedRemoveTask(sched_t *sched, ilrd_uid_t uid)
{
	task_t *task = NULL;

	assert(NULL != sched);

	task = PQErase(sched->p_queue, &SchedHelperIsMatch, &uid);
	if (NULL == task)
	{
		return;
	}

	free(task);
	task = NULL;
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                     */
/******************************************************************************/
static int SchedHelperIsBefore(const void *data_1, const void *data_2, void *param)
{
	return ((task_t *)data_1)->next_run_time > ((task_t *)data_2)->next_run_time;
}

static int SchedHelperIsMatch(const void *data, const void *param)
{
	assert(NULL != data);

	return UIDIsEqual(((task_t *)data)->uid, *((ilrd_uid_t *)param));
}
/******************************************************************************/