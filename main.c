/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:52:54 by cdahne            #+#    #+#             */
/*   Updated: 2025/10/30 18:18:49 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	synchronize_start(t_data *data)
{
	data->start_in_ms = timestamp_ms(0);
	setlong(&data->data_mutex, &data->threads_created, 1);
}

int	create_threads(t_data *data)
{
	int			i;

	i = 0;
	if (data->num_phils == 1)
	{
		if (pthread_create(&data->phils[0].id, NULL, \
			&ft_phil_single, &data->phils[0]) != 0)
			return (1);
	}
	else
	{
		while (i < data->num_phils)
		{
			if (pthread_create(&data->phils[i].id, NULL, \
				&ft_phil, &data->phils[i]) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phils)
	{
		if (pthread_join(data->phils[i++].id, NULL) != 0)
			return (1);
	}
	return (0);
}

int	philosophers(t_data	*data)
{
	if (pthread_create(&data->monitor_id, NULL, &monitor_death, data) != 0)
		return (1);
	create_threads(data);
	synchronize_start(data);
	join_threads(data);
	setlong(&data->data_mutex, &data->all_full, 1);
	if (pthread_join(data->monitor_id, NULL) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

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
