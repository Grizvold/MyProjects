#ifndef __TIME_H__
#define __TIME_H__

#include <time.h>

/*  -Returns difference between <current_time> and <next_time> */
time_t TimeDiff(time_t next_time, time_t curr_time);

/*  -Returns current time.  */
time_t TimeCurrTime();

#endif /* __TIME_H__ */