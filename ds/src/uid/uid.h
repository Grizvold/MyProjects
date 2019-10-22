#ifndef __UID_H__
#define __UID_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /* time_t, pid_t */

typedef struct uid ilrd_uid_t;

ilrd_uid_t UIDCreate();

int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2);

int UIDIsError(ilrd_uid_t uid);

struct uid
{
	time_t curr_time;
	size_t counter;
	pid_t pid;
	int is_error;
};

#endif /* __UID_H__ */
