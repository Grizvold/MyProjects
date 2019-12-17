#ifndef __SIGNAL_MANAGER_H_OL767__
#define __SIGNAL_MANAGER_H_OL767__

#include <sys/types.h> /*pid_t*/

/******************************************************************************/
/*                          Signal_Manager Functions Declaration              */
/******************************************************************************/

/*  -Create schedular with 2 signals: send_signal & receive_signal  */
void SchedularActivate(char **argv, pid_t pid);
/******************************************************************************/
#endif /* __SIGNAL_MANAGER_H_OL767__ */


