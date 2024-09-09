/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:11:29 by victor            #+#    #+#             */
/*   Updated: 2024/09/08 15:17:25 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_value_substract(	struct timeval time_minuend, \
								struct timeval time_substrahend)
{
	long	time_minuend_total_value;
	long	time_substrahend_total_value;

	time_minuend_total_value = (time_minuend.tv_sec * MILLI) \
								+ (time_minuend.tv_usec / MILLI);
	time_substrahend_total_value = (time_substrahend.tv_sec * MILLI) \
								+ (time_substrahend.tv_usec / MILLI);
	return (time_minuend_total_value - time_substrahend_total_value);
}

void	*timestamp_routine(void	*time_ptr)
{
	t_time			*time;
	struct timeval	time_current;
	struct timeval	time_program_start;
	t_monitor		*monitor;

	time = time_ptr;
	monitor = time->monitor;
	while (monitor->go == false)
		usleep(100);
	gettimeofday(&time_program_start, NULL);
	while (monitor->go == true)
	{
		pthread_mutex_lock(&time->mutex);
		gettimeofday(&time_current, NULL);
		time->timestamp = time_value_substract(time_current, \
											time_program_start);
		pthread_mutex_unlock(&time->mutex);
		usleep(50);
	}
	return (NULL);
}

uint32_t	timestamp_request(t_time *time_stamp)
{
	uint32_t	time_current;

	pthread_mutex_lock(&time_stamp->mutex);
	time_current = time_stamp->timestamp;
	pthread_mutex_unlock(&time_stamp->mutex);
	return (time_current);
}

bool	should_print(t_monitor *monitor)
{
	if (monitor->go == false)
		return (false);
	return (true);
}

void	print_message(	t_monitor *monitor, \
						const char *message, \
						uint32_t timestamp, \
						uint32_t id)
{
	if (!should_print(monitor))
		return ;
	pthread_mutex_lock(&monitor->can_print);
	printf(message, timestamp, id);
	pthread_mutex_unlock(&monitor->can_print);
}
