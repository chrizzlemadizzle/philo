/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:10:12 by cdahne            #+#    #+#             */
/*   Updated: 2025/10/30 18:20:06 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>

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
			break ;
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - '0';
		s++;
	}
	return (sign * res);
}

void	ft_log(t_phil *phil, int action)
{
	pthread_mutex_t	data_mutex;
	long			start;

	data_mutex = phil->data->data_mutex;
	start = start;
	if (phil->full)
		return ;
	pthread_mutex_lock(&phil->data->write_mutex);
	if (action == DIYING)
		printf("%08lu %d died\n", timestamp_ms(start), phil->index);
	else if (action == FORK_OWN && !getlong(&data_mutex, &phil->data->death))
		printf("%08lu %d has taken a fork\n", timestamp_ms(start), phil->index);
	else if (action == FORK_NEIGH && !getlong(&data_mutex, &phil->data->death))
		printf("%08lu %d has taken a fork\n", timestamp_ms(start), phil->index);
	else if (action == EATING && !getlong(&data_mutex, &phil->data->death))
		printf("%08lu %d is eating\n", timestamp_ms(start), phil->index);
	else if (action == SLEEPING && !getlong(&data_mutex, &phil->data->death))
		printf("%08lu %d is sleeping\n", timestamp_ms(start), phil->index);
	else if (action == THINKING && !getlong(&data_mutex, &phil->data->death))
		printf("%08lu %d is thinking\n", timestamp_ms(start), phil->index);
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
