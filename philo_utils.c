#include "philo.h"

int	ft_atol(char *s)
{
	long	sign;
	long	res;

	sign = 1;
	res = 0;
	while (*s)
	{
		if (*s == '+' || *s == ' ' || *s == '\t')
			s++;
		else if (*s == '-')
		{
			sign *= -1;
			s++;
		}
		else
			break;
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - '0';
		s++;
	}
	return (sign * res);
}

int	check_data(t_data *data)
{
	if (data->num_phils < 1)
	{
		printf("One or more Philosophers required.\n");
		return (1);
	}
	if (data->to_die < 60 || data->to_eat < 60 || data->to_sleep < 60)
	{
		printf("Please provide durations longer than 60ms.\n");
		return (1);
	}
	if (data->num_phils > INT_MAX ||\
		data->to_die > INT_MAX ||\
		data->to_eat > INT_MAX ||\
		data->to_sleep > INT_MAX ||\
		data->must_eat > INT_MAX)
	{
		printf("Please provide arguments within the scope of INT.\n");
		return (1);
	}
	return (0);
}

void	ft_log(t_phil *phil, int action)
{
	if (phil->full) // make it thread safe?!?!
		return ;
	pthread_mutex_lock(&phil->data->write_mutex);
	if (action == DIYING)
		printf("%08lu %d died\n", make_timestamp_in_ms(phil->data->start_in_ms), phil->index);
	else if (action == FORK_OWN && !getlong(&phil->data->data_mutex, &phil->data->death))
		printf("%08lu %d has taken a fork\n", make_timestamp_in_ms(phil->data->start_in_ms), phil->index);
	else if (action == FORK_NEIGH && !getlong(&phil->data->data_mutex, &phil->data->death))
		printf("%08lu %d has taken a fork\n", make_timestamp_in_ms(phil->data->start_in_ms), phil->index);
	else if (action == RELEASE_OWN && !getlong(&phil->data->data_mutex, &phil->data->death))
		printf("%08lu %d released his own fork\n", make_timestamp_in_ms(phil->data->start_in_ms), phil->index);
	else if (action == RELEASE_OWN && !getlong(&phil->data->data_mutex, &phil->data->death))
		printf("%08lu %d released his neighbour's fork\n", make_timestamp_in_ms(phil->data->start_in_ms), phil->index);
	else if (action == EATING && !getlong(&phil->data->data_mutex, &phil->data->death))
		printf("%08lu %d is eating\n", make_timestamp_in_ms(phil->data->start_in_ms), phil->index);
	else if (action == SLEEPING && !getlong(&phil->data->data_mutex, &phil->data->death))
		printf("%08lu %d is sleeping\n", make_timestamp_in_ms(phil->data->start_in_ms), phil->index);
	else if (action == THINKING && !getlong(&phil->data->data_mutex, &phil->data->death))
		printf("%08lu %d is thinking\n", make_timestamp_in_ms(phil->data->start_in_ms), phil->index);
	pthread_mutex_unlock(&phil->data->write_mutex);
}

void	terminate(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phils)
	{
		pthread_mutex_destroy(&data->phils[i].fork_mutex);
		pthread_mutex_destroy(&data->phils[i].phil_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	free(data->phils);
}
