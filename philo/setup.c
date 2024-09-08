/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:06 by vvobis            #+#    #+#             */
/*   Updated: 2024/09/08 16:28:31 by victor           ###   ########.fr       */
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

static void	fork_create(t_fork *fork)
{
	if (pthread_mutex_init(fork, NULL) != 0)
	{
		perror("fork %d mutex init");
	}
}

void	monitor_create(t_monitor *monitor, t_parameters params)
{
	unsigned int	i;

	i = 0;
	memset(monitor, 0, sizeof(*monitor));
	monitor->params = params;
	monitor->fork = malloc(sizeof(*monitor->fork) * \
			(params.philosopher_count + 1));
	monitor->philosopher = malloc(sizeof(*monitor->philosopher) \
			* params.philosopher_count);
	if (!monitor->philosopher || !monitor->fork)
		return ;
	if (pthread_mutex_init(&monitor->timestamp.mutex, NULL) != 0 \
			|| pthread_mutex_init(&monitor->can_print, NULL))
	{
		printf("timestamp_mutex init failed\n");
		return ;
	}
	monitor->timestamp.monitor = monitor;
	while (i < params.philosopher_count)
	{
		fork_create(&monitor->fork[i]);
		philosopher_create(&monitor->philosopher[i], i, monitor);
		i++;
	}
}

void	philosopher_create(t_philosopher *philosopher, \
							unsigned int identifier, t_monitor *monitor)
{
	memset(philosopher, 0, sizeof(*philosopher));
	if (pthread_mutex_init(&philosopher->mutex, NULL) != 0)
	{
		printf("philosopher mutex_state_is_changing init failed");
		return ;
	}
	philosopher->identifier = identifier;
	philosopher->monitor = monitor;
}

void	monitor_destroy(t_monitor *monitor)
{
	unsigned int	i;

	i = 0;
	while (i < monitor->params.philosopher_count)
	{
		pthread_mutex_destroy(&monitor->fork[i]);
		pthread_mutex_unlock(&monitor->philosopher[i].mutex);
		pthread_mutex_destroy(&monitor->philosopher[i].mutex);
		i++;
	}
	ft_free((void **)&monitor->philosopher);
	ft_free((void **)&monitor->fork);
}
