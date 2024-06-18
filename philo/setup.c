/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:10:06 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/17 19:00:05 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

t_monitor	*monitor_create(unsigned int number_of_philosophers)
{
	t_monitor		*monitor;
	unsigned int	i;

	monitor = malloc(sizeof(*monitor));
	if (!monitor)
		return (NULL);
	memset(monitor, 0, sizeof(*monitor));
	i = 0;
	monitor->fork = malloc(sizeof(monitor->fork) * number_of_philosophers);
	monitor->philosopher = malloc(sizeof(monitor->philosopher) * number_of_philosophers);
	monitor->number_of_philosophers = number_of_philosophers;
	monitor->mutex_can_print = malloc(sizeof(*monitor->mutex_can_print));
	monitor->mutex_checking = malloc(sizeof(*monitor->mutex_can_print));
	if (!monitor->fork || !monitor->philosopher || !monitor->mutex_can_print)
	{
		ft_free((void **)monitor->mutex_can_print);
		ft_free((void **)&monitor->fork);
		ft_free((void **)&monitor->philosopher);
		ft_free((void **)&monitor);
		return (NULL);
	}
	pthread_mutex_init(monitor->mutex_can_print, NULL);
	pthread_mutex_init(monitor->mutex_checking, NULL);
	while (i < number_of_philosophers)
	{
		monitor->fork[i] = fork_create(i);
		monitor->philosopher[i] = philosopher_create(i, monitor);
		if (!monitor->fork[i] || !monitor->philosopher[i])
		{
			while (i > 0)
			{
				philosopher_destroy(monitor->philosopher[i]);
				fork_destroy(monitor->fork[--i]);
			}
			ft_free((void **)&monitor);
			ft_free((void **)&monitor->fork);
			ft_free((void **)&monitor->philosopher);
			return (NULL);
		}
		i++;
	}
	return (monitor);
}

t_philosopher	*philosopher_create(unsigned int identifier, t_monitor *monitor)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(*philosopher));
	if (!philosopher)
		return (NULL);
	memset(philosopher, 0, sizeof(*philosopher));
	philosopher->time_last_meal = malloc(sizeof(*philosopher->time_last_meal));
	philosopher->mutex_state_is_changing = malloc(sizeof(*philosopher->mutex_state_is_changing));
	if (!philosopher->mutex_state_is_changing)
		return (ft_free((void **)&philosopher), NULL);
	if (pthread_mutex_init(philosopher->mutex_state_is_changing, NULL) != 0)
	{
		printf("philosopher mutex_state_is_changing init failed");
		return (ft_free((void **)&philosopher->mutex_state_is_changing), ft_free((void **)&philosopher), NULL);
	}
	gettimeofday(philosopher->time_last_meal, NULL);
	philosopher->identifier = identifier;
	philosopher->monitor = monitor;
	return (philosopher);
}

t_fork	*fork_create(unsigned int identifier)
{
	t_fork	*fork;

	fork = malloc(sizeof(*fork));
	if (!fork)
		return (NULL);
	memset(fork, 0, sizeof(*fork));
	fork->mutex_is_grabbed = malloc(sizeof(*fork->mutex_is_grabbed));
	if (!fork->mutex_is_grabbed)
		return (NULL);
	if (pthread_mutex_init(fork->mutex_is_grabbed, NULL) != 0)
	{
		perror("fork %d mutex init");
		exit(0);
	}
	fork->identifier = identifier;
	return (fork);
}

void	fork_destroy(t_fork *fork)
{
	pthread_mutex_destroy(fork->mutex_is_grabbed);
	ft_free((void **)&fork->mutex_is_grabbed);
	ft_free((void **)&fork);
}

void	philosopher_destroy(t_philosopher *philosopher)
{
	pthread_mutex_destroy(philosopher->mutex_state_is_changing);
	ft_free((void **)&philosopher->time_last_meal);
	ft_free((void **)&philosopher->mutex_state_is_changing);
	ft_free((void **)&philosopher);
}

void	monitor_destroy(t_monitor *monitor)
{
	unsigned int	i;

	i = 0;
	while (i < monitor->number_of_philosophers)
	{
		philosopher_destroy(monitor->philosopher[i]);
		fork_destroy(monitor->fork[i]);
		i++;
	}
	pthread_mutex_destroy(monitor->mutex_can_print);
	pthread_mutex_destroy(monitor->mutex_checking);
	ft_free((void **)&monitor->philosopher);
	ft_free((void **)&monitor->fork);
	ft_free((void **)&monitor->mutex_can_print);
	ft_free((void **)&monitor->mutex_checking);
	ft_free((void **)&monitor);
}
