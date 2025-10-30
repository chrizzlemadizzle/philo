#include "philo.h"

long	make_timestamp_in_ms(long start)
{
	struct timeval	tv;
	long			timestamp_in_ms;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	timestamp_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (timestamp_in_ms < start)
		return (-1);
	return (timestamp_in_ms - start);
}

long	gettime_in_us(void)
{
	struct timeval	tv;
	long			time_in_us;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	time_in_us = tv.tv_sec * 1e6 + tv.tv_usec;
	return (time_in_us);
}

void	custom_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remain;

	start = gettime_in_us();
	while (gettime_in_us() - start < usec)
	{
		if (getlong(&data->data_mutex, &data->death))
			break;
		elapsed = gettime_in_us() - start;
		remain = usec - elapsed;
		if (remain > 1e3)
			usleep(remain / 2);
		else
		{
			while (gettime_in_us() - start < usec)
				;
		}
	}
}
