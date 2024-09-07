/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/09/07 15:24:32 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

long	time_value_substract(struct timeval time_minuend, struct timeval time_substrahend)
{
	long time_minuend_total_value;
	long time_substrahend_total_value;

	time_minuend_total_value = (time_minuend.tv_sec * MILLISECONDS_CONVERTER) + (time_minuend.tv_usec / MILLISECONDS_CONVERTER);
	time_substrahend_total_value = (time_substrahend.tv_sec * MILLISECONDS_CONVERTER) + (time_substrahend.tv_usec / MILLISECONDS_CONVERTER);
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
		usleep(50);
	gettimeofday(&time_program_start, NULL);
	while (monitor->go == true)
	{
		pthread_mutex_lock(&time->mutex);
		gettimeofday(&time_current, NULL);
		time->timestamp = time_value_substract(time_current, time_program_start);
		pthread_mutex_unlock(&time->mutex);
		usleep(10);
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

void	print_message(t_monitor *monitor, const char *message, uint32_t timestamp, uint32_t id)
{
	if (!should_print(monitor))
		return ;
	usleep(20);
	pthread_mutex_lock(&monitor->can_print);
	printf(message, timestamp, id);
	pthread_mutex_unlock(&monitor->can_print);
}

void	grab_forks(t_philosopher *philosopher, t_monitor *monitor, t_fork *fork[2], t_time *time)
{

	pthread_mutex_lock(fork[LEFT]);
	print_message(monitor, "%u %u has taken a fork\n", timestamp_request(time), *(uint32_t *)philosopher);
	pthread_mutex_lock(fork[RIGHT]);
	print_message(monitor, "%u %u has taken a fork\n", timestamp_request(time), *(uint32_t *)philosopher);
	pthread_mutex_lock(&philosopher->mutex);
	philosopher->time_last_meal = timestamp_request(time);
	philosopher->times_eaten++;
	pthread_mutex_unlock(&philosopher->mutex);
	print_message(monitor, "%u %u is eating\n", timestamp_request(time), *(uint32_t *)philosopher);
	usleep(MILLISECONDS_CONVERTER * monitor->params.time_to_eat);
}

void	release_forks(t_philosopher *philosopher, t_fork *fork[2], t_time *time)
{
	pthread_mutex_unlock(fork[LEFT]);
	pthread_mutex_unlock(fork[RIGHT]);
	print_message(philosopher->monitor, "%u %u is sleeping\n", timestamp_request(time), *(uint32_t *)philosopher);
	usleep(MILLISECONDS_CONVERTER * philosopher->monitor->params.time_to_sleep);
}

void	set_forks(t_fork *fork[2], t_fork *monitor_forks, uint32_t id, uint32_t number_of_philosophers)
{
	if (id == number_of_philosophers - 1) // Last philosopher
	{
		if (id % 2 == 0)
		{
			fork[0] = &monitor_forks[id];		   // Right fork
			fork[1] = &monitor_forks[0];			// Left fork (wrap around to 0)
		}
		else
		{
			fork[0] = &monitor_forks[0];		   // Right fork
			fork[1] = &monitor_forks[id];			// Left fork (wrap around to 0)
		}
	}
	else
	{
		if (id % 2 == 0)
		{
			fork[0] = &monitor_forks[id];       // Left fork
			fork[1] = &monitor_forks[id + 1];   // Right fork
		}
		else
		{
			fork[0] = &monitor_forks[id + 1];   // Right fork
			fork[1] = &monitor_forks[id];       // Left fork
		}
	}
}

void	routine(t_philosopher *philosopher, t_monitor *monitor, t_fork *fork[2])
{
	pthread_mutex_t	*can_print;
	t_time			*time;

	time = &monitor->timestamp;
	can_print = &monitor->can_print;
	grab_forks(philosopher, monitor, fork, time);
	release_forks(philosopher, fork, time);
	print_message(monitor, "%u %u is thinking\n", timestamp_request(time), *(uint32_t *)philosopher);
	usleep(50);
}

void	*philosopher_routine_start(void *philosopher_input)
{
	t_philosopher	*philosopher;
	t_monitor		*monitor;
	t_fork			*fork[2];

	philosopher = philosopher_input;
	monitor = philosopher->monitor;
	set_forks(fork, monitor->fork, philosopher->identifier, monitor->params.philosopher_count);
	philosopher->is_ready = true;
	while (monitor->go != true)
		usleep(100);
	while (monitor->go == true)
		routine(philosopher, monitor, fork);
	return (NULL);
}

void	philosophers_are_ready(t_philosopher *philosophers, uint32_t number_of_philosophers)
{
	uint32_t	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		while (philosophers[i].is_ready != true)
			usleep(100);
		i++;
	}
}

void	check_params(t_monitor *monitor, t_philosopher *philosopher)
{
	t_parameters	parameters;
	int32_t			timestamp;

	parameters = monitor->params;
	pthread_mutex_lock(&philosopher->mutex);
	timestamp = (int64_t)(timestamp_request(&monitor->timestamp));
	if ((timestamp - philosopher->time_last_meal) > parameters.time_to_die)
	{
		monitor->go = false;
		usleep(100);
		pthread_mutex_lock(&monitor->can_print);
		printf("%u %u died\n", timestamp, philosopher->identifier);
		pthread_mutex_unlock(&monitor->can_print);
	}
	pthread_mutex_unlock(&philosopher->mutex);
}

void	*monitor_loop(void *monitor_input)
{
	uint32_t		i;
	t_monitor		*monitor;
	t_philosopher	*philosopher;
	uint32_t		number_of_philosophers;

	monitor = monitor_input;
	philosophers_are_ready(monitor->philosopher, monitor->params.philosopher_count);
	monitor->go = true;
	philosopher = monitor->philosopher;
	number_of_philosophers = monitor->params.philosopher_count;
	while (monitor->go)
	{
		i = 0;
		while (i < number_of_philosophers && monitor->go == true)
		{
			check_params(monitor, &philosopher[i]);
			usleep(100);
		}
	}
	return (NULL);
}

void	print_help(void)
{
	printf("Invalid arguments!\nExpected: ./philo <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]"
			"\nAccepted value range from [0..INT_MAX]\n");
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
				if ((j != 0 && argv[i][j - (j > 0)] != '+'))
					return (false);
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
		params->times_should_eat = ft_atol(argv[5], &too_big);
	else
		params->times_should_eat = -1;
	if (too_big > 0)
		return (false);
	return (true);
}

void	cancel_threads(uint32_t i, t_monitor *monitor)
{
	uint32_t	j;

	j = 0;
	while (j < i)
	{
		if (monitor->philosopher[j].is_ready == true)
			pthread_mutex_lock(&monitor->philosopher[j++].mutex);
		else
			usleep(100);
	}
	monitor->go = true;
	usleep(100);
	monitor->go = false;
	j = 0;
	while (j < i)
		pthread_mutex_unlock(&monitor->philosopher[j++].mutex);
}

int main(int argc, char **argv)
{
	pthread_t		*thread;
	t_monitor		monitor;
	t_parameters	params;
	int64_t			i;

	if (parameters_setup(&params, argc, &argv[1]))
	{
		monitor_create(&monitor, params);
		thread = malloc(sizeof(*thread) * (params.philosopher_count + 1));
		if (thread)
		{
				pthread_create(&thread[0], NULL, timestamp_routine, &monitor.timestamp);
				pthread_detach(thread[0]);
				i = 0;
				while (i < params.philosopher_count)
				{
					if (pthread_create(&thread[i + 1], NULL, philosopher_routine_start, &monitor.philosopher[i]) != 0)
					{
						print_help();
						cancel_threads(i, &monitor);
						break ;
					}
					i++;
				}
				monitor_loop(&monitor);
				while (i > 0)
					pthread_join(thread[i--], NULL);
			monitor_destroy(&monitor);
			ft_free(&thread);
		}
	}
	return (0);
}
