/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:10:27 by cdahne            #+#    #+#             */
/*   Updated: 2025/10/30 18:39:21 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5)
	{
		printf("Please enter: num_phils to_die to_eat to_sleep (meals_max)\n");
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
	if (data->num_phils > INT_MAX || \
		data->to_die > INT_MAX || \
		data->to_eat > INT_MAX || \
		data->to_sleep > INT_MAX || \
		data->meals_max > INT_MAX)
	{
		printf("Please provide arguments within the scope of INT.\n");
		return (1);
	}
	return (0);
}
