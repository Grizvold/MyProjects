#include <time.h> /*    time_t     */

#include "time.h" /*    time API   */

time_t TimeDiff(time_t next_time, time_t curr_time)
{
    return next_time - curr_time;
}

time_t TimeCurrTime()
{
    return time(NULL);
}
