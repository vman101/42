/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:46:11 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/13 16:46:55 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_message_check_death(t_philosopher *philosopher, \
									t_monitor *monitor, \
									const char *message)
{
	uint32_t	timestamp;
	bool		ret;

	timestamp = timestamp_request(monitor->start, monitor);
	pthread_mutex_lock(&monitor->mutex);
	if ((int)(timestamp - philosopher->time_last_meal) \
			>= (int)monitor->params.time_to_die && monitor->go != 2)
	{
		ret = true;
		monitor->go = 2;
		printf("%u %u died in phil\n", timestamp, philosopher->identifier + 1);
	}
	else
	{
		ret = false;
		if (message && monitor->go != 2)
			printf("%u %u %s\n", timestamp, \
					philosopher->identifier + 1, message);
	}
	pthread_mutex_unlock(&monitor->mutex);
	return (ret);
}

void	philosopher_sleep(t_philosopher *philosopher, \
							t_monitor *monitor, \
							int64_t time_to_sleep)
{
	while (time_to_sleep > 0)
	{
		print_message_check_death(philosopher, monitor, NULL);
		usleep(philosopher->sleep_chunk);
		time_to_sleep -= philosopher->sleep_chunk;
	}
}
