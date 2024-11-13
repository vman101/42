/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:11:29 by victor            #+#    #+#             */
/*   Updated: 2024/10/16 15:38:09 by vvobis           ###   ########.fr       */
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

uint32_t	timestamp_request(struct timeval time_start, t_monitor *monitor)
{
	struct timeval	time_current;

	if (gettimeofday(&time_current, NULL) != 0)
		monitor_set(monitor, 2);
	return (time_value_substract(time_current, time_start));
}
