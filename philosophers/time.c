/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:11:29 by victor            #+#    #+#             */
/*   Updated: 2024/11/15 16:31:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	time_value_substract(	struct timeval time_minuend, \
									uint64_t time_substrahend)
{
	uint64_t	time_minuend_total_value;

	time_minuend_total_value = (time_minuend.tv_sec * MILLI * MILLI) \
								+ (time_minuend.tv_usec);
	return (time_minuend_total_value - time_substrahend);
}

uint64_t	timestamp_request(uint64_t time_start, t_monitor *monitor)
{
	struct timeval	time_current;

	if (gettimeofday(&time_current, NULL) != 0)
		monitor_set(monitor, 2);
	return (time_value_substract(time_current, time_start));
}
