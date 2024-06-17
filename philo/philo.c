/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/17 17:11:51 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/types/struct_timeval.h>

long	time_value_substract(t_time time_minuend, t_time time_substrahend)
{
	long time_minuend_total_value;
	long time_substrahend_total_value;

	time_minuend_total_value = (time_minuend.tv_sec * MILLISECONDS_CONVERTER) + (time_minuend.tv_usec / MILLISECONDS_CONVERTER);
	time_substrahend_total_value = (time_substrahend.tv_sec * MILLISECONDS_CONVERTER) + (time_substrahend.tv_usec / MILLISECONDS_CONVERTER);
	return (time_minuend_total_value - time_substrahend_total_value);
}

void	philosopher_state_print(t_philosopher *philosopher, uint8_t const *philosopher_state)
{
	pthread_mutex_lock(philosopher->monitor->mutex_can_print);
	printf("%d %d %s\n", philosopher->monitor->time_stamp, philosopher->identifier, philosopher_state);
	pthread_mutex_unlock(philosopher->monitor->mutex_can_print);
}

void	*philosopher_routine_start(void *philosopher_input)
{
	t_philosopher	*philosopher;
	t_monitor		*monitor;
	t_fork			*switch_fork;
	t_time			rand;

	philosopher = philosopher_input;
	monitor = philosopher->monitor;
	pthread_mutex_lock(philosopher->mutex_state_is_changing);
	gettimeofday(philosopher->time_last_meal, NULL);
	pthread_mutex_unlock(philosopher->mutex_state_is_changing);
	if (philosopher->identifier == 0)
		philosopher->first_fork_grabbed = monitor->fork[monitor->number_of_philosophers - 1];
	else
		philosopher->first_fork_grabbed = monitor->fork[philosopher->identifier];
	if (philosopher->identifier == monitor->number_of_philosophers - 1)
		philosopher->second_fork_grabbed = monitor->fork[0];
	else
		philosopher->second_fork_grabbed = monitor->fork[philosopher->identifier + 1];
	while (monitor->philosopher_dead == false)
	{
		gettimeofday(&rand, NULL);
		if (rand.tv_usec % 2)
		{
			switch_fork = philosopher->first_fork_grabbed;
			philosopher->first_fork_grabbed = philosopher->second_fork_grabbed;
			philosopher->second_fork_grabbed = switch_fork;
		}
		pthread_mutex_lock(philosopher->first_fork_grabbed->mutex_is_grabbed);
		pthread_mutex_lock(philosopher->second_fork_grabbed->mutex_is_grabbed);
		/*printf("philosopher %d is eating\n", philosopher->identifier);*/
		pthread_mutex_lock(philosopher->mutex_state_is_changing);
		gettimeofday(philosopher->time_last_meal, NULL);
		pthread_mutex_unlock(philosopher->mutex_state_is_changing);
		usleep(TIME_TO_EAT * MILLISECONDS_CONVERTER);
		pthread_mutex_unlock(philosopher->first_fork_grabbed->mutex_is_grabbed);
		pthread_mutex_unlock(philosopher->second_fork_grabbed->mutex_is_grabbed);
		/*printf("philosopher %d is sleeping\n", philosopher->identifier);*/
		usleep(TIME_TO_SLEEP * MILLISECONDS_CONVERTER);
		/*printf("philosopher %d is thinking\n", philosopher->identifier);*/
	}
	return (NULL);
}

int main()
{
	pthread_t		*philosopher_thread;
	void			*thread_return_value;
	t_monitor		*monitor;
	t_philosopher	*philosopher_current;
	t_time			time_program_start;
	t_time			time_current;
	unsigned int	i;

	gettimeofday(&time_program_start, NULL);
	monitor = monitor_create(NUM_PHILOSOPHERS);
	thread_return_value = malloc(sizeof(*thread_return_value));
	philosopher_thread = malloc(sizeof(*philosopher_thread) * NUM_PHILOSOPHERS);
	if (!monitor || !thread_return_value || !philosopher_thread)
	{
		ft_free((void **)&monitor);
		ft_free((void **)&thread_return_value);
		return (1);
	}
	i = 0;
	while (i < NUM_PHILOSOPHERS)
	{
		pthread_create(&philosopher_thread[i], NULL, philosopher_routine_start, monitor->philosopher[i]);
		i++;
	}
	monitor->philosopher_dead = false;

	while (!monitor->philosopher_dead)
	{
		i = 0;
		while (i < NUM_PHILOSOPHERS)
		{
			philosopher_current = monitor->philosopher[i];
			pthread_mutex_lock(philosopher_current->mutex_state_is_changing);
			gettimeofday(&time_current, NULL);
			int64_t time = time_value_substract(time_current, *philosopher_current->time_last_meal);
			printf("%ld\n", time);
			if (time > TIME_TO_DIE)
			{
				printf("philosopher %d died\n", philosopher_current->identifier);
				exit( 0 );
			}
			pthread_mutex_unlock(philosopher_current->mutex_state_is_changing);
			i++;
		}
	}
	ft_free((void **)&philosopher_thread);
	ft_free((void **)&thread_return_value);
	return (0);
}
