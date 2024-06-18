/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/19 01:14:12 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

void	philosopher_mutex_lock(t_philosopher *philosopher, pthread_mutex_t *mutex, uint32_t mode)
{
	if (philosopher->monitor->philosopher_dead == true)
		return ;
	pthread_mutex_lock(philosopher->mutex_state_is_changing);
	pthread_mutex_lock(mutex);
	if (mode != NONE)
	{
		philosopher->state = mode;
		philosopher->state_has_changed = true;
	}
	pthread_mutex_unlock(philosopher->mutex_state_is_changing);
}

void	philosopher_mutex_unlock(t_philosopher *philosopher, pthread_mutex_t *mutex, uint32_t mode)
{
	if (philosopher->monitor->philosopher_dead == true)
		return ;
	pthread_mutex_lock(philosopher->mutex_state_is_changing);
	pthread_mutex_unlock(mutex);
	if (mode != NONE)
	{
		philosopher->state = mode;
		philosopher->state_has_changed = true;
	}
	pthread_mutex_unlock(philosopher->mutex_state_is_changing);
}

void	philosopher_sleep(t_philosopher *philosopher, unsigned int time_to_sleep)
{
	if (philosopher->monitor->philosopher_dead == true)
		return ;
	pthread_mutex_lock(philosopher->mutex_state_is_changing);
	philosopher->state = SLEEPING;
	philosopher->state_has_changed = true;
	pthread_mutex_unlock(philosopher->mutex_state_is_changing);
	usleep(time_to_sleep * MILLISECONDS_CONVERTER);
}

void	philosopher_eat(t_philosopher *philosopher, unsigned int time_to_eat)
{
	if (philosopher->monitor->philosopher_dead == true)
		return ;
	pthread_mutex_lock(philosopher->mutex_state_is_changing);
	gettimeofday(philosopher->time_last_meal, NULL);
	philosopher->state = EATING;
	philosopher->state_has_changed = true;
	pthread_mutex_unlock(philosopher->mutex_state_is_changing);
	usleep(time_to_eat * MILLISECONDS_CONVERTER);
}

long	time_value_substract(t_time time_minuend, t_time time_substrahend)
{
	long time_minuend_total_value;
	long time_substrahend_total_value;

	time_minuend_total_value = (time_minuend.tv_sec * MILLISECONDS_CONVERTER) + (time_minuend.tv_usec / MILLISECONDS_CONVERTER);
	time_substrahend_total_value = (time_substrahend.tv_sec * MILLISECONDS_CONVERTER) + (time_substrahend.tv_usec / MILLISECONDS_CONVERTER);
	return (time_minuend_total_value - time_substrahend_total_value);
}

void	philosopher_state_print(t_philosopher *philosopher)
{
	unsigned int	philosopher_state;

	pthread_mutex_lock(philosopher->mutex_state_is_changing);
	if (philosopher->first_fork_grabbed == true && philosopher->second_fork_grabbed == false && philosopher->state_has_changed == true)
	{
		printf("%u %d has taken a fork\n", philosopher->monitor->time_stamp, philosopher->identifier);
		philosopher->state_has_changed = false;
	}
	if (philosopher->second_fork_grabbed  == true &&  philosopher->state_has_changed == true)
	{
		printf("%u %d has taken a fork\n", philosopher->monitor->time_stamp, philosopher->identifier);
		philosopher->state_has_changed = false;
	}
	philosopher_state = philosopher->state;
	if (philosopher->state_has_changed == true)
	{
		if (philosopher_state == EATING)
			printf("%u %d is eating\n", philosopher->monitor->time_stamp, philosopher->identifier);
		else if (philosopher_state == SLEEPING)
			printf("%u %d is sleeping\n", philosopher->monitor->time_stamp, philosopher->identifier);
		else if (philosopher_state == THINKING)
			printf("%u %d is thinking\n", philosopher->monitor->time_stamp, philosopher->identifier);
		else if (philosopher_state == DEAD)
			printf("%u %d died\n", philosopher->monitor->time_stamp, philosopher->identifier);
		philosopher->state_has_changed = false;
	}
	pthread_mutex_unlock(philosopher->mutex_state_is_changing);
}

void	*philosopher_routine_start(void *philosopher_input)
{
	t_philosopher	*philosopher;
	t_monitor		*monitor;
	t_fork			*switch_fork;

	philosopher = philosopher_input;
	monitor = philosopher->monitor;
	pthread_mutex_lock(philosopher->mutex_state_is_changing);
	gettimeofday(philosopher->time_last_meal, NULL);
	pthread_mutex_unlock(philosopher->mutex_state_is_changing);
	if (philosopher->identifier == 0)
		philosopher->first_fork = monitor->fork[monitor->number_of_philosophers - 1];
	else
		philosopher->first_fork = monitor->fork[philosopher->identifier];
	if (philosopher->identifier == monitor->number_of_philosophers - 1)
		philosopher->second_fork = monitor->fork[0];
	else
		philosopher->second_fork = monitor->fork[philosopher->identifier + 1];
	while (monitor->philosopher_dead == false)
	{
		if (philosopher->time_last_meal->tv_usec % 2)
		{
			usleep(100);
			switch_fork = philosopher->first_fork;
			philosopher->first_fork = philosopher->second_fork;
			philosopher->second_fork = switch_fork;
		}
		philosopher_mutex_lock(philosopher, philosopher->first_fork->mutex_is_grabbed, NONE);
		philosopher->first_fork_grabbed = true;
		philosopher_mutex_lock(philosopher, philosopher->second_fork->mutex_is_grabbed, EATING);
		philosopher->second_fork_grabbed = true;
		philosopher_eat(philosopher, TIME_TO_EAT);
		philosopher_mutex_unlock(philosopher, philosopher->second_fork->mutex_is_grabbed, NONE);
		philosopher->first_fork_grabbed = false;
		philosopher_mutex_unlock(philosopher, philosopher->first_fork->mutex_is_grabbed, SLEEPING);
		philosopher->second_fork_grabbed = false;
		philosopher_sleep(philosopher, TIME_TO_SLEEP);
		philosopher->state = THINKING;
	}
	return (&philosopher->identifier);
}

void	*monitor_loop(void *monitor_input)
{
	size_t			i;
	t_monitor		*monitor;
	t_philosopher	*philosopher_current;
	t_time			time_program_start;
	t_time			time_current;

	monitor = monitor_input;
	gettimeofday(&time_program_start, NULL);
	monitor->philosopher_dead = false;
	monitor->can_print = true;
	while (!monitor->philosopher_dead)
	{
		i = 0;
		while (i < NUM_PHILOSOPHERS && monitor->philosopher_dead == false)
		{
			philosopher_current = monitor->philosopher[i];
			gettimeofday(&time_current, NULL);
			int64_t time = time_value_substract(time_current, *philosopher_current->time_last_meal);
			monitor->time_stamp = time_value_substract(time_current, time_program_start);
			/*pthread_mutex_lock(philosopher_current->mutex_state_is_changing);*/
			if (time > TIME_TO_DIE)
			{
				philosopher_current->state = DEAD;
				monitor->philosopher_dead = true;
			}
			if (philosopher_current->state_has_changed == true)
				philosopher_state_print(philosopher_current);
			/*pthread_mutex_unlock(philosopher_current->mutex_state_is_changing);*/
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

int main()
{
	pthread_t		*philosopher_thread;
	pthread_t		*monitor_thread;
	int				*thread_return_value;
	t_monitor		*monitor;
	unsigned int	i;

	monitor = monitor_create(NUM_PHILOSOPHERS);
	philosopher_thread = malloc(sizeof(*philosopher_thread) * NUM_PHILOSOPHERS);
	monitor_thread = malloc(sizeof(*monitor_thread));
	if (!monitor ||  !philosopher_thread)
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
	pthread_create(monitor_thread, NULL, monitor_loop, monitor);
	i = 0;
	while (monitor->philosopher_dead == false)
		sleep(1);

	pthread_mutex_unlock(monitor->mutex_can_print);
	pthread_mutex_destroy(monitor->mutex_can_print);
	monitor_destroy(monitor);
	ft_free((void **)&philosopher_thread);
	ft_free((void **)&monitor_thread);
	return (0);
}
