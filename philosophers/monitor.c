/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:16:54 by victor            #+#    #+#             */
/*   Updated: 2024/11/18 10:52:19 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_set(t_monitor *monitor, uint8_t go)
{
	pthread_mutex_lock(&monitor->mutex);
	monitor->go = go;
	pthread_mutex_unlock(&monitor->mutex);
}

void	check_params(	t_monitor *monitor, \
						int64_t timestamp, \
						t_philosopher *philosopher, \
						t_parameters *params)
{
	uint32_t	i;

	i = 0;
	pthread_mutex_lock(&monitor->mutex);
	while (i < params->philosopher_count)
	{
		timestamp = timestamp_request(monitor->start, monitor);
		if ((int64_t)(timestamp - philosopher[i].time_last_meal) \
				>= params->time_to_die && monitor->go != 2)
		{
			monitor->go = 2;
			printf("%lu %u died\n", timestamp / 1000, i + 1);
		}
		if (params->times_should_eat != -1 \
			&& philosopher[i].times_eaten >= params->times_should_eat)
			params->finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&monitor->mutex);
}

void	monitor_loop(t_monitor *monitor)
{
	t_parameters	params;

	params = monitor->params;
	if (monitor->valid_count != params.philosopher_count \
			|| params.times_should_eat == 0)
		return ;
	while (monitor_check(monitor) != 2)
	{
		params.finished_eating = 0;
		check_params(monitor, timestamp_request(monitor->start, monitor), \
				monitor->philosopher, &params);
		if (params.times_should_eat != -1 && \
			(int64_t)params.finished_eating == params.philosopher_count)
			monitor_set(monitor, 2);
		usleep(100);
	}
}

void	print_help(void)
{
	printf("Invalid arguments!\nExpected: ./philo <number_of_philosophers> " \
			"<time_to_die> <time_to_eat> <time_to_sleep> " \
			"[number_of_times_each_philosopher_must_eat]" \
			"\nAccepted value range from [0..INT_MAX]\n");
}
