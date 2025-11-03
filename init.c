/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:10:18 by cdahne            #+#    #+#             */
/*   Updated: 2025/11/03 12:13:25 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		data->meals_max = ft_atol(argv[5]);
	else
		data->meals_max = -1;
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

	i = 0;
	while (i < data->num_phils)
	{
		data->phils[i].index = i + 1;
		pthread_mutex_init(&data->phils[i].fork_mutex, NULL);
		data->phils[i].meals = 0;
		if (data->meals_max == 0)
			data->phils[i].full = 1;
		else
			data->phils[i].full = 0;
		if (i > 0)
			data->phils[i].neighbour = &data->phils[i - 1];
		data->phils[i].data = data;
		pthread_mutex_init(&data->phils[i].phil_mutex, NULL);
		i++;
	}
	data->phils[0].neighbour = &data->phils[i - 1];
	return (0);
}
