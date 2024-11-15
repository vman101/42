/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:45:09 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/15 16:24:46 by vvobis           ###   ########.fr       */
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
	int32_t				times_eaten;
	uint32_t			time_last_meal;
	struct s_monitor	*monitor;
	uint64_t			start;
	pthread_mutex_t		*mutex;
	t_parameters		params;
	uint32_t			sleep_chunk;
	int					left_fork;
	int					right_fork;
}	t_philosopher;

typedef struct s_monitor
{
	uint8_t			go;
	uint32_t		valid_count;
	pthread_mutex_t	mutex;
	t_fork			*fork;
	t_philosopher	*philosopher;
	t_parameters	params;
	uint64_t		start;
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

/* time.c */
uint64_t	timestamp_request(uint64_t time, t_monitor *monitor);
uint64_t		time_value_substract(	struct timeval time_minuend, \
									uint64_t time_substrahend);
uint8_t		monitor_check(t_monitor *monitor);
void		monitor_set(t_monitor *monitor, uint8_t go);

/* routine */
void		*philosopher_routine_start(void *philosopher_input);

/* monitoring.c */
void		print_help(void);
void		monitor_loop(t_monitor *monitor_input);
void		single_philo(t_monitor *monitor);

void		philosopher_sleep(t_philosopher *philosopher, \
								int64_t time_to_sleep);

bool		print_message_check_death(t_philosopher *philosopher, \
										t_monitor *monitor, \
										const char *message);
#endif
