/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:16:54 by victor            #+#    #+#             */
/*   Updated: 2024/09/08 15:17:45 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers_are_ready(	t_philosopher *philosophers, \
								uint32_t number_of_philosophers)
{
	uint32_t	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		while (philosophers[i].is_ready != true)
			usleep(200);
		i++;
	}
}

void	check_params(	t_monitor *monitor, \
						t_philosopher *philosopher, \
						t_parameters *params)
{
	int32_t			timestamp;

	pthread_mutex_lock(&philosopher->mutex);
	timestamp = (int64_t)(timestamp_request(&monitor->timestamp));
	if ((timestamp - philosopher->time_last_meal) > params->time_to_die)
	{
		monitor->go = false;
		pthread_mutex_lock(&monitor->can_print);
		printf("%u %u died\n", timestamp, philosopher->identifier);
		pthread_mutex_unlock(&monitor->can_print);
	}
	if (params->times_should_eat != -1 \
		&& (int64_t)philosopher->times_eaten >= params->times_should_eat)
		params->finished_eating++;
	pthread_mutex_unlock(&philosopher->mutex);
}

void	*monitor_loop(void *monitor_input)
{
	uint32_t		i;
	t_monitor		*monitor;
	t_philosopher	*philosopher;
	t_parameters	params;

	monitor = monitor_input;
	philosophers_are_ready(monitor->philosopher, \
			monitor->params.philosopher_count);
	monitor->go = true;
	philosopher = monitor->philosopher;
	params = monitor->params;
	while (monitor->go)
	{
		i = 0;
		if (params.times_should_eat != -1 && \
				(int64_t)params.finished_eating == params.philosopher_count)
			monitor->go = false;
		params.finished_eating = 0;
		while (i < params.philosopher_count && monitor->go == true)
		{
			usleep(100);
			check_params(monitor, &philosopher[i++], &params);
		}
	}
	return (NULL);
}

void	print_help(void)
{
	printf("Invalid arguments!\nExpected: ./philo <number_of_philosophers> " \
			"<time_to_die> <time_to_eat> <time_to_sleep> " \
			"[number_of_times_each_philosopher_must_eat]" \
			"\nAccepted value range from [0..INT_MAX]\n");
}

void	cancel_threads(uint32_t i, t_monitor *monitor)
{
	uint32_t	j;

	j = 0;
	while (j < i)
	{
		if (monitor->philosopher[j].is_ready == true)
			pthread_mutex_lock(&monitor->philosopher[j++].mutex);
		else
			usleep(100);
	}
	monitor->go = true;
	usleep(100);
	monitor->go = false;
	j = 0;
	while (j < i)
		pthread_mutex_unlock(&monitor->philosopher[j++].mutex);
}
