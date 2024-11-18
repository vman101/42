/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/18 10:43:42 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_monitor *monitor)
{
	if (monitor->params.philosopher_count == 0)
		return ;
	pthread_mutex_lock(&monitor->mutex);
	printf("%lu %u has taken a fork\n", \
			timestamp_request(monitor->start, monitor), \
			monitor->philosopher->identifier + 1);
	pthread_mutex_unlock(&monitor->mutex);
}

bool	thread_start(pthread_t *thread, t_monitor *monitor, \
						t_philosopher *philo, uint64_t time_usec)
{
	philo->start = time_usec;
	if (pthread_create(thread, NULL, philosopher_routine_start, \
				philo) != 0)
	{
		pthread_mutex_lock(&monitor->mutex);
		printf("Encountered error Creating threads: " \
				"%d threads created\n", philo->identifier);
		monitor->go = 2;
		pthread_mutex_unlock(&monitor->mutex);
		return (false);
	}
	return (true);
}

static void	main_loop(t_monitor *monitor, \
						pthread_t **thread, \
						t_parameters params)
{
	int64_t			i;
	struct timeval	time;
	uint64_t		time_usec;

	i = 0;
	if (gettimeofday(&time, NULL) != 0)
		return ;
	time_usec = time.tv_sec * 1000000 + time.tv_usec;
	monitor->start = time_usec;
	while (i < params.philosopher_count)
	{
		if (!thread_start(&(*thread)[i], monitor, \
					&monitor->philosopher[i], time_usec))
			break ;
		i++;
	}
	if (i == params.philosopher_count)
		monitor_loop(monitor);
	while (--i >= 0)
		if (pthread_join((*thread)[i], NULL) != 0)
			printf("Failed to join with thread %ld\n", i);
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_monitor		monitor;
	t_parameters	params;

	thread = NULL;
	if (parameters_setup(&params, argc, &argv[1]) \
			&& params.philosopher_count > 0 && (params.times_should_eat == -1 \
				|| params.times_should_eat > 0))
	{
		monitor_create(&monitor, params);
		thread = malloc(sizeof(*thread) * (params.philosopher_count));
		if (thread)
			if (monitor.valid_count == params.philosopher_count)
				main_loop(&monitor, &thread, params);
		monitor_destroy(&monitor);
	}
	else
		print_help();
	ft_free(&thread);
	return (0);
}
