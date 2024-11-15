/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/15 16:32:51 by vvobis           ###   ########.fr       */
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

static bool	validate_input(char **argv)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				if (argv[i][j] == '+' \
						&& (j == 0 || argv[i][j - (j > 0)] != '+'))
					;
				else
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static bool	parameters_setup(t_parameters *params, \
							int argc, char **argv)
{
	uint8_t	too_big;

	if (argc < 5 || argc > 6 || !validate_input(argv))
		return (false);
	too_big = 0;
	params->philosopher_count = ft_atol(argv[0], &too_big);
	params->time_to_die = ft_atol(argv[1], &too_big) * 1000;
	params->time_to_eat = ft_atol(argv[2], &too_big) * 1000;
	params->time_to_sleep = ft_atol(argv[3], &too_big) * 1000;
	params->times_should_eat = -1;
	params->finished_eating = 0;
	if (argc > 5)
		params->times_should_eat = ft_atol(argv[4], &too_big);
	if (too_big > 0)
		return (false);
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
		monitor->philosopher[i].start = time_usec;
		if (pthread_create(&(*thread)[i], NULL, philosopher_routine_start, \
					&monitor->philosopher[i]) != 0)
		{
			pthread_mutex_lock(&monitor->mutex);
			printf("Encountered error Creating threads: " \
					"%ld threads created\n", i);
			monitor->go = 2;
			pthread_mutex_unlock(&monitor->mutex);
			break ;
		}
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
