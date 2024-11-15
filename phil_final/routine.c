/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:10:05 by victor            #+#    #+#             */
/*   Updated: 2024/11/15 16:49:35 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pick_up_fork(t_fork *fork, int id, \
		t_monitor *monitor, t_philosopher *philosopher)
{
	pthread_mutex_lock(&fork[id]);
	print_message_check_death(philosopher, monitor, "has taken a fork");
}

static void	grab_forks(	t_philosopher *philosopher, \
						t_monitor *monitor, \
						t_fork *fork)
{
	if (philosopher->identifier % 2)
	{
		pick_up_fork(fork, philosopher->left_fork, monitor, philosopher);
		pick_up_fork(fork, philosopher->right_fork, monitor, philosopher);
	}
	else
	{
		pick_up_fork(fork, philosopher->right_fork, monitor, philosopher);
		pick_up_fork(fork, philosopher->left_fork, monitor, philosopher);
	}
	usleep(10);
	pthread_mutex_lock(&monitor->mutex);
	if (monitor->go != 2)
		printf("%lu %u is eating\n", \
		timestamp_request(philosopher->start, monitor) / 1000, \
		philosopher->identifier + 1);
	philosopher->time_last_meal = timestamp_request(philosopher->start, \
			monitor);
	pthread_mutex_unlock(&monitor->mutex);
	philosopher_sleep(philosopher, monitor->params.time_to_eat);
}

static void	release_forks(	t_philosopher *philosopher, \
							t_fork *fork, \
							t_monitor *monitor)
{
	if (philosopher->identifier % 2)
	{
		pthread_mutex_unlock(&fork[philosopher->right_fork]);
		pthread_mutex_unlock(&fork[philosopher->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&fork[philosopher->left_fork]);
		pthread_mutex_unlock(&fork[philosopher->right_fork]);
	}
	usleep(10);
	pthread_mutex_lock(philosopher->mutex);
	if (philosopher->monitor->go != 2)
	{
		printf("%lu %u died in phil\n", \
				timestamp_request(philosopher->start, monitor) / 1000, \
				philosopher->identifier + 1);
	}
	philosopher->times_eaten++;
	pthread_mutex_unlock(philosopher->mutex);
	philosopher_sleep(philosopher, philosopher->params.time_to_sleep);
}

static void	routine(t_philosopher *philosopher, \
					t_monitor *monitor, \
					t_fork *fork)
{
	grab_forks(philosopher, monitor, fork);
	release_forks(philosopher, fork, monitor);
	print_message_check_death(philosopher, monitor, "is thinking");
}

void	*philosopher_routine_start(void *philosopher_input)
{
	t_philosopher	*philosopher;
	t_monitor		*monitor;

	philosopher = philosopher_input;
	monitor = philosopher->monitor;
	if (philosopher->identifier % 2 != 0)
		usleep(1000);
	if (monitor->params.philosopher_count < 2)
		return (single_philo(monitor), NULL);
	while (monitor_check(monitor) != 2)
	{
		routine(philosopher, monitor, monitor->fork);
		usleep(10);
	}
	return (NULL);
}
