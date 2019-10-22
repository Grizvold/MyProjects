#ifndef __SCHED_H__
#define __SCHED_H__

#include <stddef.h> /* size_t */

#include "uid.h"

typedef struct sched sched_t;

typedef int(*operation_func_t)(void *param);

sched_t *SchedCreate();

uid_t SchedAddTast(sched_t *sched, size_t interval_sec, operation_func_t act_func, void *param);

void SchedRemove(sched_t *sched, uid_t task);

void SchedRun(sched_t *sched);

void SchedStop(sched_t *sched);

void SchedDestroy(sched_t *sched);

#endif /* __SCHED_H__ */
