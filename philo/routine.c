/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:10:05 by victor            #+#    #+#             */
/*   Updated: 2024/09/08 15:14:21 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_forks(	t_philosopher *philosopher, \
						t_monitor *monitor, \
						t_fork *fork[2], \
						t_time *time)
{
	pthread_mutex_lock(fork[LEFT]);
	print_message(monitor, "%u %u has taken a fork\n", \
			timestamp_request(time), *(uint32_t *)philosopher);
	if (monitor->params.philosopher_count == 1)
		return ;
	pthread_mutex_lock(fork[RIGHT]);
	print_message(monitor, "%u %u has taken a fork\n", \
			timestamp_request(time), *(uint32_t *)philosopher);
	pthread_mutex_lock(&philosopher->mutex);
	philosopher->time_last_meal = timestamp_request(time);
	philosopher->times_eaten++;
	pthread_mutex_unlock(&philosopher->mutex);
	usleep(MILLI * monitor->params.time_to_eat);
	print_message(monitor, "%u %u is eating\n", \
			timestamp_request(time), *(uint32_t *)philosopher);
}

static void	release_forks(	t_philosopher *philosopher, \
							t_fork *fork[2], \
							t_monitor *monitor, \
							t_time *time)
{
	pthread_mutex_unlock(fork[LEFT]);
	if (monitor->params.philosopher_count == 1)
		return ;
	pthread_mutex_unlock(fork[RIGHT]);
	usleep(MILLI * philosopher->monitor->params.time_to_sleep);
	print_message(philosopher->monitor, "%u %u is sleeping\n", \
			timestamp_request(time), *(uint32_t *)philosopher);
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
			return (usleep(200), \
					fork[0] = &monitor_forks[id], \
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
	if (monitor->params.philosopher_count == 1)
		return ;
	print_message(monitor, "%u %u is thinking\n", \
			timestamp_request(&monitor->timestamp), *(uint32_t *)philosopher);
	if (philosopher->identifier % 2 == 0)
		usleep(50);
	else
		usleep(20);
}

void	*philosopher_routine_start(void *philosopher_input)
{
	t_philosopher	*philosopher;
	t_monitor		*monitor;
	t_fork			*fork[2];

	philosopher = philosopher_input;
	monitor = philosopher->monitor;
	set_forks(fork, monitor->fork, philosopher->identifier, \
			monitor->params.philosopher_count);
	philosopher->is_ready = true;
	while (monitor->go != true)
		usleep(200);
	while (monitor->go == true)
	{
		routine(philosopher, monitor, fork);
		if (monitor->params.philosopher_count == 1)
			return (NULL);
	}
	return (NULL);
}
