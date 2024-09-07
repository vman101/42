/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:45:09 by vvobis            #+#    #+#             */
/*   Updated: 2024/09/06 16:47:55 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>

# define MILLISECONDS_CONVERTER 1000

# define NUM_PHILOSOPHERS	4
# define TIME_TO_DIE		400
# define TIME_TO_EAT		200
# define TIME_TO_SLEEP		200

# define TRUE				1
# define FALSE				0

# define SHOULD_EXIT do { printf("Should exit clean\n"); } while (0);

typedef struct	timeval	t_time;

typedef struct	s_fork
{
	bool			is_grabed;
	unsigned int	identifier;
	pthread_mutex_t	mutex_is_grabbed;
}				t_fork;

typedef struct	s_philosopher
{
	uint8_t				state;
	bool				state_has_changed;
	bool				first_fork_grabbed;
	bool				second_fork_grabbed;
	bool				is_ready;
	t_fork				*first_fork;
	t_fork				*second_fork;
	unsigned int		identifier;
	t_time				time_last_meal;
	pthread_mutex_t		mutex_state_is_changing;
	struct s_monitor	*monitor;
}				t_philosopher;

typedef struct	s_monitor
{
	bool					philosopher_dead;
	pthread_mutex_t			mutex_can_print;
	bool					can_print;
	bool					go;
	pthread_mutex_t			mutex_checking;
	unsigned int			number_of_philosophers;
	t_time					start_time;
	uint32_t				time_stamp;
	t_fork					*fork;
	struct s_philosopher	*philosopher;
}				t_monitor;

enum e_mode
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	NONE,
};

enum e_philosopher_offset
{
	STATE,
	FIRST_FORK_GRABBED,
	SECOND_FORK_GRABBED,
};

/* utils */
void			ft_free(void *ptr);

/* philo */
void			fork_create(t_fork *fork, unsigned int identifier);
void			monitor_create(t_monitor *monitor, unsigned int number_of_philosophers);
void			philosopher_create(t_philosopher *philosopher, unsigned int identifier, t_monitor *monitor);
void			fork_destroy(t_fork *fork);
void			philosopher_destroy(t_philosopher *philosopher);
void			monitor_destroy(t_monitor *monitor);

/* Routine Functions */

void	philosopher_state_change(t_philosopher *philosopher, uint32_t philosopher_state_offset, uint8_t philosopher_state_new, bool philosopher_state_is_changed);

#endif
