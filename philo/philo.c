/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/09/08 16:30:06 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (argc > 5)
		params->times_should_eat = ft_atol(argv[4], &too_big);
	else
		params->times_should_eat = -1;
	if (too_big > 0)
		return (false);
	return (true);
}

void	warning(t_parameters params)
{
	printf("There seem to be more than 1000 threads.\n"
		"This warning sets an arbitrary limit just for completeness.\n"
		"You can try and wait fo all %d thread to be created...\n", \
		params.philosopher_count);
}

void	main_loop(t_monitor *monitor, pthread_t *thread, t_parameters params)
{
	int64_t			i;

	monitor_create(monitor, params);
	thread = malloc(sizeof(*thread) * (params.philosopher_count + 1));
	if (!thread)
		return ;
	pthread_create(&thread[0], NULL, timestamp_routine, &monitor->timestamp);
	i = 0;
	while (i < params.philosopher_count)
	{
		if (pthread_create(&thread[i + 1], NULL, philosopher_routine_start, \
					&monitor->philosopher[i]) != 0)
		{
			print_help();
			cancel_threads(i, monitor);
			break ;
		}
		else if (i == 1000)
			warning(params);
		i++;
	}
	monitor_loop(monitor);
	while (i > 0)
		pthread_join(thread[i--], NULL);
	monitor_destroy(monitor);
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_monitor		monitor;
	t_parameters	params;

	thread = NULL;
	if (parameters_setup(&params, argc, &argv[1]))
		main_loop(&monitor, thread, params);
	ft_free(&thread);
	return (0);
}
