#include <stddef.h> /* size_t */
#include <sys/types.h> /*  */
#include <time.h> /* time_t/time */
#include <unistd.h>

#include "uid.h"

ilrd_uid_t UIDCreate()
{
	ilrd_uid_t new_uid = {0};
	static size_t counter = 0;
	
	new_uid.curr_time = time(NULL);
	new_uid.counter = counter++;
	new_uid.pid = getpid(); /* getpid returns unique process id */
	
	/* error check for time_t */
	if((time_t)(-1) == new_uid.curr_time)
	{
		new_uid.is_error = 1;
	}
	
	return new_uid;
}

int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2)
{

	return (uid1.curr_time == uid2.curr_time 
			&& uid1.counter == uid2.counter
			&& uid1.pid == uid2.pid
			&& uid1.is_error == uid2.is_error);
}

int UIDIsError(ilrd_uid_t uid)
{

	return uid.is_error;
}


