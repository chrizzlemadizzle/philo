#include "philo.h"

int		all_threads_running(pthread_mutex_t *mutex, long *threads, long num_phils)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (*threads == num_phils)
		ret = 1;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	ft_eating(t_phil *phil)
{
	if (phil->index % 2 == 0)
	{
		pthread_mutex_lock(&phil->fork_mutex);
		ft_log(phil, FORK_OWN);
		pthread_mutex_lock(&phil->neighbour->fork_mutex);
		ft_log(phil, FORK_NEIGH);
	}
	else
	{
		pthread_mutex_lock(&phil->neighbour->fork_mutex);
		ft_log(phil, FORK_NEIGH);
		pthread_mutex_lock(&phil->fork_mutex);
		ft_log(phil, FORK_OWN);
	}
	setlong(&phil->phil_mutex, &phil->last_meal_in_ms, make_timestamp_in_ms(0));
	phil->meals++;
	ft_log(phil, EATING);
	custom_usleep(phil->data->to_eat * 1000, phil->data);
	if (phil->data->must_eat > 0 && phil->meals == phil->data->must_eat)
		setlong(&phil->phil_mutex, &phil->full, 1);
	pthread_mutex_unlock(&phil->fork_mutex);
	pthread_mutex_unlock(&phil->neighbour->fork_mutex);
}

void	ft_sleeping(t_phil *phil)
{
	ft_log(phil, SLEEPING);
	custom_usleep(phil->data->to_sleep * 1000, phil->data);
	return ;
}

void	ft_thinking(t_phil *phil)
{
	long	to_think;

	ft_log(phil, THINKING);
	if (phil->data->num_phils % 2 == 1)
	{
		to_think = 2 * phil->data->to_eat - phil->data->to_sleep;
		if (to_think < 0)
			to_think = 0;
		custom_usleep(to_think * 1000 * 0.5, phil->data);
	}
	return ;
}
