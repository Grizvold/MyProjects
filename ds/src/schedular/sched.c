#include <stddef.h> /* size_t */
#include <stdio.h>  /* perror */


#include "sched.h"
#include "pq.h"
#include "uid.h"

/*########################### typedefs ################################*/

struct sched
{
	pq_t *p_queue;
};

typedef struct task
{
	ilrd_uid_t task_id;
	size_t interval_sec;
	time_t next_time;
	opration_func_t action_func;
	void *action_func_param;
}task_t;

/*#####################################################################*/

/*######################## Auxiliary Func #############################*/

int IsBefore(void *data_1, void *data_2, void *param);

/*#####################################################################*/

/*####################### Schedule Funtionality #######################*/

sched_t *SchedCreate()
{
	sched_t *new_sched = NULL;
	
	new_sched = (sched_t *)malloc(sizeof(*new_sched));
	if(NULL == new_sched)
	{
		perror("SchedCreate malloc failed");
		
		return NULL;
	}
	
	new_sched->p_queue = PQCreate(&IsBefore, NULL);
	if(NULL == new_sched->p_queue)
	{
		perror("SchedCreate PQCreate malloc failed");
		
		free(new_sched);
		
		return NULL;
	}
	
	return new_sched;
}

uid_t SchedAddTask(sched_t *sched,
 				size_t interval_sec, 
 				operation_func_t act_func, 
 				void *param)
{
	
}

/*#####################################################################*/

/*######################## Auxiliary Func #############################*/

int IsBefore(void *data_1, void *data_2, void *param)
{
	
}

/*#####################################################################*/
