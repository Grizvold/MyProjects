#ifndef __TASK_H__
#define __TASK_H__

#include "sched.h" /*  */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef struct task
{
    ilrd_uid_t uid;
    operation_func_t func;
    void *func_param;
    size_t interval_time; /* interval between every execution */
    time_t next_run_time; /* time untill next execution */
} task_t;

/*  -Creates new task.  
    -Returns pointer to the created task.   */
task_t *TaskCreate(size_t interval_in_seconds, operation_func_t func, void *param);

/*  -Run requested task.
    -Returns:
        1 to keep running.
        0 to stop the task. */
int TaskRun(task_t *task);
/******************************************************************************/
#endif /* __TASK_H__ */