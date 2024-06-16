/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:45:09 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/16 22:35:42 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
#include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct	s_fork
{
	unsigned int	identifier;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct	s_philosopher
{
	unsigned int		identifier;
	unsigned char		mode;
	struct timeval		last_meal;
	struct s_monitor	*monitor;
}				t_philosopher;

typedef struct	s_monitor
{
	unsigned int			number_of_philosophers;
	unsigned int			current_philosopher;
	bool					philosopher_dead;
	struct timeval			start_time;
	t_fork					**fork;
	struct s_philosopher	**philosopher;
}				t_monitor;

enum e_mode
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
};

/* utils */
void			ft_free(void **ptr);

/* philo */
t_fork			*fork_create(unsigned int identifier);
t_monitor		*monitor_create(unsigned int number_of_philosophers);
t_philosopher	*philosopher_create(unsigned int identifier, t_monitor *monitor);
void			fork_destroy(t_fork *fork);
void			philosopher_destroy(t_philosopher *philosopher);

#endif
