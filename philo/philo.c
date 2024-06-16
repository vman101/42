/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/16 23:16:05 by victor           ###   ########.fr       */
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

void	*p_fork_grab(void *philosopher_input)
{
	t_philosopher	*philosopher;
	unsigned int	number_of_philosophers;
	unsigned int	left_hand_fork;
	unsigned int	right_hand_fork;
	unsigned int	switch_fork;
	struct timeval	time;

	philosopher = philosopher_input;
	number_of_philosophers = philosopher->monitor->number_of_philosophers;
	gettimeofday(&time, NULL);
	if (philosopher->identifier == 0)
		left_hand_fork = philosopher->monitor->fork[number_of_philosophers - 1]->identifier;
	else
		left_hand_fork = philosopher->identifier - 1;
	if (philosopher->identifier == number_of_philosophers -1)
		right_hand_fork = 0;
	else
		right_hand_fork = philosopher->identifier;
	if (time.tv_sec % 2 == 0)
	{
		switch_fork = left_hand_fork;
		left_hand_fork = right_hand_fork;
		right_hand_fork = switch_fork;
	}
	while (1)
	{
		if (philosopher->monitor->philosopher_dead == true)
			break ;
		pthread_mutex_lock(&philosopher->monitor->fork[left_hand_fork]->mutex);
		pthread_mutex_lock(&philosopher->monitor->fork[right_hand_fork]->mutex);
		printf("philosopher %d is eating\n", philosopher->identifier);
		philosopher->mode = EATING;
		gettimeofday(&philosopher->last_meal, NULL);
		usleep(200000);
		pthread_mutex_unlock(&philosopher->monitor->fork[left_hand_fork]->mutex);
		pthread_mutex_unlock(&philosopher->monitor->fork[right_hand_fork]->mutex);
		printf("philosopher %d is sleeping\n", philosopher->identifier);
		philosopher->mode = SLEEPING;
		usleep(200000);
	}
	return (&philosopher->identifier);
}

t_monitor	*monitor_create(unsigned int number_of_philosophers)
{
	t_monitor		*monitor;
	unsigned int	i;

	monitor = malloc(sizeof(*monitor));
	if (!monitor)
		return (NULL);
	i = 0;
	monitor->fork = malloc(sizeof(monitor->fork) * number_of_philosophers);
	monitor->philosopher = malloc(sizeof(monitor->philosopher) * number_of_philosophers);
	monitor->number_of_philosophers = number_of_philosophers;
	if (!monitor->fork || !monitor->philosopher)
	{
		ft_free((void **)&monitor->fork);
		ft_free((void **)&monitor->philosopher);
		ft_free((void **)&monitor);
		return (NULL);
	}
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
	pthread_mutex_init(&fork->mutex, NULL);
	fork->identifier = identifier;
	return (fork);
}

void	fork_destroy(t_fork *fork)
{
	pthread_mutex_destroy(&fork->mutex);
	ft_free((void **)&fork);
}

void	philosopher_destroy(t_philosopher *philosopher)
{
	ft_free((void **)&philosopher);
}

#define NUM_PHILOSOPHERS 1

void	*start_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = arg;
	printf("philosopher %d is thinking\n", philosopher->identifier);
	return (NULL);
}

int main()
{
	pthread_t		*philosopher_thread;
	void			*thread_return_value;
	t_monitor		*monitor;
	unsigned int	i;

	monitor = monitor_create(NUM_PHILOSOPHERS);
	thread_return_value = malloc(sizeof(*thread_return_value));
	philosopher_thread = malloc(sizeof(*philosopher_thread) * NUM_PHILOSOPHERS);
	if (!monitor || !thread_return_value || !philosopher_thread)
	{
		ft_free((void **)&monitor);
		ft_free((void **)&thread_return_value);
		return (1);
	}
	i = 0;
	while (i < NUM_PHILOSOPHERS)
	{
		monitor->current_philosopher = i;
		pthread_create(&philosopher_thread[i], NULL, p_fork_grab, monitor->philosopher[i]);
		i++;
	}
	monitor->philosopher_dead = false;
	while (!monitor->philosopher_dead)
	{
		i = 0;
		while (i < NUM_PHILOSOPHERS && !monitor->philosopher_dead)
		{
			struct timeval	time;
			gettimeofday(&time, NULL);
			if (time.tv_usec - monitor->philosopher[i]->last_meal.tv_usec > 800000)
			{
				printf("philosopher %d died\n", i);
				monitor->philosopher[i]->mode = DEAD;
				monitor->philosopher_dead = true;
				i = 0;
				while (i < NUM_PHILOSOPHERS)
				{
					pthread_detach(philosopher_thread[i]);
					i++;
				}
			}
			i++;
		}
	}
	ft_free((void **)&philosopher_thread);
	ft_free((void **)&thread_return_value);
	return (0);
}
