/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:06 by vvobis            #+#    #+#             */
/*   Updated: 2024/09/06 16:50:14 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(void *ptr_ptr)
{
	void **ptr = ptr_ptr;
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	monitor_create(t_monitor *monitor, unsigned int number_of_philosophers)
{
	unsigned int	i;

	i = 0;
	memset(monitor, 0, sizeof(*monitor));
	monitor->fork = malloc(sizeof(*monitor->fork) * number_of_philosophers);
	monitor->philosopher = malloc(sizeof(*monitor->philosopher) * number_of_philosophers);
	if (!monitor->philosopher || !monitor->fork)
		SHOULD_EXIT
	monitor->number_of_philosophers = number_of_philosophers;
	pthread_mutex_init(&monitor->mutex_checking, NULL);
	while (i < number_of_philosophers)
	{
		fork_create(&monitor->fork[i], i);
		philosopher_create(&monitor->philosopher[i], i, monitor);
		i++;
	}
}

void	philosopher_create(t_philosopher *philosopher, unsigned int identifier, t_monitor *monitor)
{
	memset(philosopher, 0, sizeof(*philosopher));
	if (pthread_mutex_init(&philosopher->mutex_state_is_changing, NULL) != 0)
	{
		printf("philosopher mutex_state_is_changing init failed");
		SHOULD_EXIT
	}
	philosopher->identifier = identifier;
	philosopher->monitor = monitor;
}

void	fork_create(t_fork *fork, unsigned int identifier)
{
	memset(fork, 0, sizeof(*fork));
	if (pthread_mutex_init(&fork->mutex_is_grabbed, NULL) != 0)
	{
		perror("fork %d mutex init");
	}
	fork->identifier = identifier;
}

void	fork_destroy(t_fork *fork)
{
	pthread_mutex_unlock(&fork->mutex_is_grabbed);
	pthread_mutex_destroy(&fork->mutex_is_grabbed);
}

void	philosopher_destroy(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->mutex_state_is_changing);
	pthread_mutex_destroy(&philosopher->mutex_state_is_changing);
}

void	monitor_destroy(t_monitor *monitor)
{
	unsigned int	i;

	i = 0;
	while (i < monitor->number_of_philosophers)
	{
		philosopher_destroy(&monitor->philosopher[i]);
		fork_destroy(&monitor->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->mutex_can_print);
	pthread_mutex_destroy(&monitor->mutex_checking);
	ft_free((void **)&monitor->philosopher);
	ft_free((void **)&monitor->fork);
}
