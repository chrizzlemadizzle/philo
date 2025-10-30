/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:07:39 by cdahne            #+#    #+#             */
/*   Updated: 2025/10/30 18:07:40 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setlong(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	getlong(pthread_mutex_t *mutex, long *src)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *src;
	pthread_mutex_unlock(mutex);
	return (ret);
}
