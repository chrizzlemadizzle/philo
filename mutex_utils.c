#include "philo.h"

void	setlong(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	getlong(pthread_mutex_t *mutex, long *src)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *src;
	pthread_mutex_unlock(mutex);
	return (ret);
}
