#include "philo.h"

void	synchronize_start(t_data *data)
{
	data->start_in_ms = make_timestamp_in_ms(0);
	setlong(&data->data_mutex, &data->threads_created, 1);
}

int	philosophers(t_data	*data)
{
	pthread_t	monitor_id;
	int	i;

	i = 0;
	if (pthread_create(&monitor_id, NULL, &monitor_death, data) != 0)
		return (1);
	if (data->num_phils == 1)
	{
		if (pthread_create(&data->phils[0].id, NULL, &ft_phil_single, &data->phils[0]) != 0)
			return (1);
	}
	else
		while (i < data->num_phils)
		{
			if (pthread_create(&data->phils[i].id, NULL, &ft_phil, &data->phils[i]) != 0)
				return (1);
			i++;
		}
	synchronize_start(data);
	i = 0;
	while (i < data->num_phils)
		if (pthread_join(data->phils[i++].id, NULL) != 0)
			return (2);
	setlong(&data->data_mutex, &data->all_full, 1);
	if (pthread_join(monitor_id, NULL) != 0)
		return (0);
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5)
	{
		printf("Please enter arguments for: 1. Number of Philosophers, 2. Time to die, 3. Time to eat, 4. Time to sleep, 5. Maximum amount of Meals per Philo (optional)\n");
		return (1);
	}
	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Please provide only numeric arguments.\n");
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int	i;

	if (check_args(argc, argv) != 0)
		return (1);
	if (init_data(&data, argv) != 0)
		return (1);
	if (init_phils(&data) != 0)
		return (1);
	philosophers(&data);
	terminate(&data);
	return (0);
}
