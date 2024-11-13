/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:06 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/13 17:12:32 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(void *ptr_ptr)
{
	void	**ptr;

	ptr = ptr_ptr;
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

uint8_t	monitor_check(t_monitor *monitor)
{
	uint8_t	res;

	res = 0;
	pthread_mutex_lock(&monitor->mutex);
	res = monitor->go;
	pthread_mutex_unlock(&monitor->mutex);
	return (res);
}

void	monitor_create(t_monitor *monitor, t_parameters params)
{
	memset(monitor, 0, sizeof(*monitor));
	monitor->params = params;
	monitor->fork = malloc(sizeof(*monitor->fork) * \
			(params.philosopher_count + 1));
	monitor->philosopher = malloc(sizeof(*monitor->philosopher) \
			* params.philosopher_count);
	if (!monitor->philosopher || !monitor->fork)
		return ;
	if (pthread_mutex_init(&monitor->mutex, NULL) != 0)
	{
		printf("timestamp_mutex init failed\n");
		return ;
	}
	if (gettimeofday(&monitor->start, NULL) != 0)
		return ;
	while (monitor->valid_count < params.philosopher_count)
	{
		if (pthread_mutex_init(&monitor->fork[monitor->valid_count], NULL) != 0)
			return ;
		philosopher_create(&monitor->philosopher[monitor->valid_count], \
				monitor->valid_count, monitor);
		monitor->valid_count++;
	}
}

void	philosopher_create(t_philosopher *philosopher, \
							unsigned int identifier, t_monitor *monitor)
{
	memset(philosopher, 0, sizeof(*philosopher));
	philosopher->identifier = identifier;
	philosopher->monitor = monitor;
	philosopher->start = monitor->start;
	philosopher->sleep_chunk = 10000;
}

void	monitor_destroy(t_monitor *monitor)
{
	unsigned int	i;

	i = 0;
	while (i < monitor->valid_count)
	{
		pthread_mutex_destroy(&monitor->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->mutex);
	ft_free(&monitor->philosopher);
	ft_free(&monitor->fork);
}
