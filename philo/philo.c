/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/15 18:27:20 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_fork_grab(void *philosopher_input)
{
	t_monitor		*monitor;
	t_philosopher	*philosopher;

	philosopher = philosopher_input;
	monitor = philosopher->monitor;
	printf("philosopher %d tries to grab the fork\n", philosopher->identifier);
	pthread_mutex_lock(&monitor->fork[philosopher->identifier]);
	printf("philosopher %d grabbed a fork\n", philosopher->identifier);
	pthread_mutex_unlock(&monitor->fork[philosopher->identifier]);

	return (NULL);
}

int main()
{
	pthread_t		**philosopher_thread;
	t_philosopher	**philosopher;
	void			*thread_return_value;
	t_monitor		*monitor;

	monitor = malloc(sizeof(*monitor));
	thread_return_value = malloc(sizeof(*thread_return_value));
	monitor->fork = malloc(sizeof(*monitor->fork) * 2);
	philosopher = malloc(sizeof(philosopher) * 2);
	philosopher[0] = malloc(sizeof(**philosopher));
	philosopher[1] = malloc(sizeof(**philosopher));
	philosopher[0]->identifier = 0;
	philosopher[1]->identifier = 1;
	philosopher[0]->monitor = monitor;
	philosopher[1]->monitor = monitor;
	philosopher_thread = malloc(sizeof(**philosopher_thread) * 2);
	philosopher_thread[0] = malloc(sizeof(*philosopher_thread));
	philosopher_thread[1] = malloc(sizeof(*philosopher_thread));
	pthread_mutex_init(&monitor->fork[0], NULL);
	pthread_mutex_init(&monitor->fork[1], NULL);
	pthread_create(philosopher_thread[1], NULL, p_fork_grab, philosopher[1]);
	pthread_create(philosopher_thread[0], NULL, p_fork_grab, philosopher[0]);
	pthread_join(*philosopher_thread[1], &thread_return_value);
	pthread_join(*philosopher_thread[0], &thread_return_value);
	free(thread_return_value);
	free(philosopher);
	return (0);
}
