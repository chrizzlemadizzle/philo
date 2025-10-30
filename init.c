#include "philo.h"

int	init_data(t_data *data, char **argv)
{
	pthread_mutex_init(&data->data_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	data->num_phils = ft_atol(argv[1]);
	data->to_die = ft_atol(argv[2]);
	data->to_eat = ft_atol(argv[3]);
	data->to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->must_eat = ft_atol(argv[5]);
	else
		data->must_eat = -1;
	if (check_data(data) != 0)
		return (1);
	data->threads_created = 0;
	data->threads_running = 0;
	data->phils = malloc(data->num_phils * sizeof(t_phil));
	if (!data->phils)
	{
		printf("Memory Allocation Error.\n");
		return (1);
	}
	data->death = 0;
	data->all_full = 0;
	return (0);
}

int	init_phils(t_data *data)
{
	int	i;
	t_phil	*phil;

	phil = data->phils;
	i = 0;
	while (i < data->num_phils)
	{
		phil[i].index = i + 1;
		pthread_mutex_init(&phil->fork_mutex, NULL);
		phil->meals = 0;
		phil->full = 0;
		if (i > 0)
			phil->neighbour = &phil[i - 1];
		phil->data = data;
		pthread_mutex_init(&phil->phil_mutex, NULL);
		i++;
	}
	phil[0].neighbour = &phil[i];
	return (0);
}
