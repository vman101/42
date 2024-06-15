/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:45:09 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/15 18:17:01 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>

typedef struct	s_mutex
{
	pthread_mutex_t *mutex;
	int				*c;
}				t_mutex;

typedef  pthread_mutex_t t_fork;

typedef struct	s_philosopher
{
	unsigned int		identifier;
	struct s_monitor	*monitor;
}				t_philosopher;

typedef struct	s_monitor
{
	t_fork					*fork;
	struct s_philosopher	*philosopher;
}				t_monitor;

#endif
