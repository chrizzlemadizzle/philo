/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:10:12 by cdahne            #+#    #+#             */
/*   Updated: 2025/11/03 12:01:11 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			break ;
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - '0';
		s++;
	}
	return (sign * res);
}

//!getlong(&data_mutex, &phil->data->death
void	ft_log(t_phil *phil, int action)
{
	long			start;

	if (phil->full)
		return ;
	start = phil->data->start_in_ms;
	if (getlong(&phil->data->data_mutex, &phil->data->death))
	{
		pthread_mutex_lock(&phil->data->write_mutex);
		if (action == DIYING)
			printf("%08lu %d died\n", tstmp_ms(start), phil->index);
		pthread_mutex_unlock(&phil->data->write_mutex);
	}
	else
	{
		pthread_mutex_lock(&phil->data->write_mutex);
		if (action == FORK)
			printf("%08lu %d has taken a fork\n", tstmp_ms(start), phil->index);
		else if (action == EATING)
			printf("%08lu %d is eating\n", tstmp_ms(start), phil->index);
		else if (action == SLEEPING)
			printf("%08lu %d is sleeping\n", tstmp_ms(start), phil->index);
		else if (action == THINKING)
			printf("%08lu %d is thinking\n", tstmp_ms(start), phil->index);
		pthread_mutex_unlock(&phil->data->write_mutex);
	}
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
