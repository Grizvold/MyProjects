#include <stdlib.h> /* malloc, free */

#include "task.h"
#include "time.h"

/************* functions ***************/

task_t *TaskCreate(size_t interval_in_seconds, operation_func_t func, void* param)
{
	task_t *task;

	while(1)
    {
        task = malloc(sizeof(*task));
        if(NULL == task)
        {
            break;
        }
	
        task->uid = UIDCreate();
        if(1 == task->uid.is_error)
        {
            break;
        }

        task->func = func;
        task->func_param = param;
        task->interval_time = interval_in_seconds; 
        task->next_run_time = TimeCurrTime() + interval_in_seconds; 

        return task;
    }

    free(task);
    task = NULL;

    return NULL;
}


int TaskRun(task_t *task) 
{
	return (task->func(task->func_param));
}
