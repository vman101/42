/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:45:09 by vvobis            #+#    #+#             */
/*   Updated: 2024/09/10 22:24:56 by vvobis           ###   ########.fr       */
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

# define MILLI 1000

# define LEFT				1
# define RIGHT				0

typedef struct s_time
{
	pthread_mutex_t		mutex;
	uint32_t			timestamp;
	struct s_monitor	*monitor;
}	t_time;

typedef pthread_mutex_t	t_fork;

typedef struct s_parameters
{
	uint32_t	philosopher_count;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	uint32_t	time_to_die;
	int32_t		times_should_eat;
	uint32_t	finished_eating;
}	t_parameters;

typedef struct s_philosopher
{
	unsigned int		identifier;
	bool				is_ready;
	uint32_t			times_eaten;
	uint32_t			time_last_meal;
	bool				left_grabbed;
	bool				right_grabbed;
	pthread_mutex_t		mutex;
	struct s_monitor	*monitor;
}	t_philosopher;

typedef struct s_monitor
{
	uint8_t			go;
	uint32_t		valid_count;
	pthread_mutex_t	mutex;
	t_time			timestamp;
	t_fork			*fork;
	t_philosopher	*philosopher;
	t_parameters	params;
}	t_monitor;

/* utils */
void		ft_free(void *ptr);
long		ft_atol(char const *s, unsigned char *too_big);

/* philo */
void		monitor_create(t_monitor *monitor, t_parameters params);
void		philosopher_create(	t_philosopher *philosopher, \
								uint32_t identifier, \
								t_monitor *monitor);
void		monitor_destroy(t_monitor *monitor);

/* Routine Functions */

/* time.c */
uint32_t	timestamp_request(t_time *time_stamp);
void		*timestamp_routine(void	*time_ptr);
long		time_value_substract(	struct timeval time_minuend, \
									struct timeval time_substrahend);
void		print_message(	t_monitor *monitor, \
							const char *message, \
							uint32_t timestamp, \
							uint32_t id);
uint8_t		monitor_check(t_monitor *monitor);
void		monitor_set(t_monitor *monitor, uint8_t go);

/* routine */
void		*philosopher_routine_start(void *philosopher_input);

/* monitoring.c */
void		print_help(void);
void		monitor_loop(t_monitor *monitor_input);
void		cancel_threads(uint32_t i, t_monitor *monitor);
void		single_philo(t_monitor *monitor);

#endif
