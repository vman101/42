/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:45:09 by vvobis            #+#    #+#             */
/*   Updated: 2024/09/07 15:20:40 by vvobis           ###   ########.fr       */
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

# define LEFT				1
# define RIGHT				0

# define SHOULD_EXIT do { printf("Should exit clean\n"); } while (0);

typedef struct	{
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
}	t_parameters;

typedef struct	s_philosopher
{
	unsigned int		identifier;
	bool				is_ready;
	uint32_t			times_eaten;
	uint32_t			time_last_meal;
	pthread_mutex_t		mutex;
	struct s_monitor	*monitor;
}				t_philosopher;

typedef struct	s_monitor
{
	bool			go;
	pthread_mutex_t	can_print;
	t_time			timestamp;
	t_fork			*fork;
	t_philosopher	*philosopher;
	t_parameters	params;
}				t_monitor;

/* utils */
void	ft_free(void *ptr);
long	ft_atol(char const *s, unsigned char *too_big);

/* philo */
void	monitor_create(t_monitor *monitor, t_parameters params);
void	philosopher_create(t_philosopher *philosopher, unsigned int identifier, t_monitor *monitor);
void	fork_destroy(t_fork *fork);
void	philosopher_destroy(t_philosopher *philosopher);
void	monitor_destroy(t_monitor *monitor);

/* Routine Functions */

void	philosopher_state_change(t_philosopher *philosopher, uint32_t philosopher_state_offset, uint8_t philosopher_state_new, bool philosopher_state_is_changed);

#endif
