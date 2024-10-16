/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:10:05 by victor            #+#    #+#             */
/*   Updated: 2024/10/05 15:49:49 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_forks(	t_philosopher *philosopher, \
						t_monitor *monitor, \
						t_fork *fork[2], \
						t_time *time)
{
	pthread_mutex_lock(fork[LEFT]);
	usleep(10);
	philosopher->left_grabbed = true;
	pthread_mutex_lock(&monitor->mutex);
	if (monitor->go != 2)
		printf("%u %u has taken a fork\n", \
			timestamp_request(time), *(uint32_t *)philosopher);
	pthread_mutex_unlock(&monitor->mutex);
	pthread_mutex_lock(fork[RIGHT]);
	philosopher->right_grabbed = true;
	pthread_mutex_lock(&monitor->mutex);
	if (monitor->go != 2)
		printf("%u %u has taken a fork\n" \
				"%u %u is eating\n",
			timestamp_request(time), *(uint32_t *)philosopher,
		timestamp_request(time), *(uint32_t *)philosopher);
	philosopher->times_eaten++;
	philosopher->time_last_meal = timestamp_request(time);
	pthread_mutex_unlock(&monitor->mutex);
	usleep(MILLI * monitor->params.time_to_eat);
}

static void	release_forks(	t_philosopher *philosopher, \
							t_fork *fork[2], \
							t_monitor *monitor, \
							t_time *time)
{
	pthread_mutex_unlock(fork[LEFT]);
	pthread_mutex_unlock(fork[RIGHT]);
	print_message(monitor, "%u %u is sleeping\n", \
		timestamp_request(time), *(uint32_t *)philosopher);
	usleep(MILLI * philosopher->monitor->params.time_to_sleep);
}

static void	set_forks(	t_fork *fork[2], \
					t_fork *monitor_forks, \
					uint32_t id, \
					uint32_t number_of_philosophers)
{
	if (id == number_of_philosophers - 1)
	{
		if (id % 2 == 0)
			return (fork[0] = &monitor_forks[id], \
					fork[1] = &monitor_forks[0], (void)0);
		else
			return (fork[0] = &monitor_forks[0], \
					fork[1] = &monitor_forks[id], (void)0);
	}
	else
	{
		if (id % 2 == 0)
			return (fork[0] = &monitor_forks[id], \
					fork[1] = &monitor_forks[id + 1], (void)0);
		else
			return (fork[0] = &monitor_forks[id + 1], \
					fork[1] = &monitor_forks[id], (void)0);
	}
}

static void	routine(t_philosopher *philosopher, \
					t_monitor *monitor, \
					t_fork *fork[2])
{
	grab_forks(philosopher, monitor, fork, &monitor->timestamp);
	release_forks(philosopher, fork, monitor, &monitor->timestamp);
	print_message(monitor, "%u %u is thinking\n", \
		timestamp_request(&monitor->timestamp), *(uint32_t *)philosopher);
}

void	*philosopher_routine_start(void *philosopher_input)
{
	t_philosopher	*philosopher;
	t_monitor		*monitor;
	t_fork			*fork[2];

	philosopher = philosopher_input;
	monitor = philosopher->monitor;
	if (philosopher->identifier % 2 == 0)
		usleep(10);
	if (monitor->params.philosopher_count < 2)
		return (single_philo(monitor), NULL);
	set_forks(fork, monitor->fork, philosopher->identifier, \
			monitor->params.philosopher_count);
	philosopher->identifier += 1;
	while (monitor_check(monitor) != 2)
	{
		routine(philosopher, monitor, fork);
		usleep(10);
	}
	return (NULL);
}
