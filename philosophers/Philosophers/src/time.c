#include "philo.h"

long long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
//void	precise_sleep(long long ms)
//{
//
//}
