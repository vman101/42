/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/05 15:28:17 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_monitor *monitor)
{
	if (monitor->params.philosopher_count == 0)
		return ;
	pthread_mutex_lock(&monitor->mutex);
	printf("%u %u has taken a fork\n", \
			timestamp_request(&monitor->timestamp), \
			monitor->philosopher->identifier + 1);
	pthread_mutex_unlock(&monitor->mutex);
}

bool	validate_input(char **argv)
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

bool	parameters_setup(t_parameters *params, int argc, char **argv)
{
	uint8_t	too_big;

	if (argc < 5 || argc > 6 || !validate_input(argv))
		return (print_help(), false);
	too_big = 0;
	params->philosopher_count = ft_atol(argv[0], &too_big);
	params->time_to_die = ft_atol(argv[1], &too_big);
	params->time_to_eat = ft_atol(argv[2], &too_big);
	params->time_to_sleep = ft_atol(argv[3], &too_big);
	params->times_should_eat = -1;
	params->finished_eating = 0;
	if (argc > 5)
		params->times_should_eat = ft_atol(argv[4], &too_big);
	if (too_big > 0)
		return (false);
	return (true);
}

void	main_loop(t_monitor *monitor, pthread_t **thread, t_parameters params)
{
	int64_t			i;

	i = 0;
	if (pthread_create(&(*thread)[0], NULL, timestamp_routine, \
				&monitor->timestamp) != 0)
		return ;
	while (i < params.philosopher_count)
	{
		if (pthread_create(&(*thread)[i + 1], NULL, philosopher_routine_start, \
					&monitor->philosopher[i]) != 0)
		{
			print_help();
			monitor_set(monitor, 2);
			break ;
		}
		i++;
	}
	if (monitor->valid_count == params.philosopher_count)
		monitor_loop(monitor);
	usleep(100);
	while (i > 0)
		if (pthread_join((*thread)[i--], NULL) != 0)
			printf("Failed to join with thread %ld\n", i);

}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_monitor		monitor;
	t_parameters	params;

	thread = NULL;
	if (parameters_setup(&params, argc, &argv[1]))
	{
		monitor_create(&monitor, params);
		thread = malloc(sizeof(*thread) * (params.philosopher_count + 1));
		if (thread)
			if (monitor.valid_count == params.philosopher_count)
				main_loop(&monitor, &thread, params);
		monitor_destroy(&monitor);
	}
	ft_free(&thread);
	return (0);
}
