/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:10:30 by cdahne            #+#    #+#             */
/*   Updated: 2025/11/03 12:02:09 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death(void *arg)
{
	t_phil	*phil;
	t_data	*data;

	data = (t_data *)arg;
	phil = data->phils;
	while (!all_threads_run(data))
		;
	while (!getlong(&data->data_mutex, &data->all_full))
	{
		if (!getlong(&phil->phil_mutex, &phil->full))
		{
			if (tstmp_ms(\
				getlong(&phil->phil_mutex, &phil->last_meal_in_ms)) \
				> data->to_die)
			{
				setlong(&data->data_mutex, &data->death, 1);
				ft_log(phil, DIYING);
				return (NULL);
			}
		}
		if (phil->index == data->num_phils)
			usleep(1000);
		phil = phil->neighbour;
	}
	return (NULL);
}

void	*ft_phil(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (!getlong(&phil->data->data_mutex, &phil->data->threads_created))
		;
	setlong(&phil->phil_mutex, &phil->last_meal_in_ms, tstmp_ms(0));
	pthread_mutex_lock(&phil->data->data_mutex);
	phil->data->threads_running++;
	pthread_mutex_unlock(&phil->data->data_mutex);
	if (phil->data->num_phils % 2 == 0 && phil->index % 2 == 0)
		custom_usleep(3e4, phil->data);
	while (!getlong(&phil->data->data_mutex, &phil->data->death))
	{
		if (phil->full)
			break ;
		ft_eating(phil);
		ft_sleeping(phil);
		ft_thinking(phil);
	}
	return (NULL);
}

void	*ft_phil_single(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (!getlong(&phil->data->data_mutex, &phil->data->threads_created))
		;
	setlong(&phil->phil_mutex, &phil->last_meal_in_ms, tstmp_ms(0));
	pthread_mutex_lock(&phil->data->data_mutex);
	phil->data->threads_running++;
	pthread_mutex_unlock(&phil->data->data_mutex);
	ft_log(phil, FORK);
	while (!getlong(&phil->data->data_mutex, &phil->data->death))
		usleep(100);
	return (NULL);
}
