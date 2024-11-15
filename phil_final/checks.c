/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:46:11 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/15 16:53:58 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_life(t_philosopher *philo)
{
	int64_t	timestamp;

	timestamp = timestamp_request(philo->start, philo->monitor);
	if ((int64_t)(timestamp - philo->time_last_meal) \
			>= philo->params.time_to_die)
	{
		pthread_mutex_lock(philo->mutex);
		if (philo->monitor->go != 2)
		{
			philo->monitor->go = 2;
			printf("%lu %u died in phil\n", timestamp / 1000, philo->identifier + 1);
		}
		pthread_mutex_unlock(philo->mutex);
	}
}

bool	print_message_check_death(t_philosopher *philosopher, \
									t_monitor *monitor, \
									const char *message)
{
	uint64_t	timestamp;

	timestamp = timestamp_request(monitor->start, monitor);
	pthread_mutex_lock(&monitor->mutex);
	if (message && monitor->go != 2)
		printf("%lu %u %s\n", timestamp / 1000, \
				philosopher->identifier + 1, message);
	pthread_mutex_unlock(&monitor->mutex);
	return (true);
}

void	philosopher_sleep(t_philosopher *philosopher, int64_t time_to_sleep)
{
	uint32_t	sleep_chunk;

	sleep_chunk = philosopher->sleep_chunk;
	while (time_to_sleep > 0)
	{
		usleep(sleep_chunk);
		time_to_sleep -= sleep_chunk;
		if (time_to_sleep < sleep_chunk)
			sleep_chunk = time_to_sleep;
		check_life(philosopher);
	}
}
