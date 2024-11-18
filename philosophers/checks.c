/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:46:11 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/18 10:34:58 by vvobis           ###   ########.fr       */
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
			printf("%lu %u died\n", timestamp / 1000, \
					philo->identifier + 1);
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

bool	parameters_setup(t_parameters *params, \
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
