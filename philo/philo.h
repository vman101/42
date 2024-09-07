/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:24:22 by vvobis            #+#    #+#             */
/*   Updated: 2024/08/29 10:32:29 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "types.h"
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_fork
{
	u8				id;
	pthread_mutex_t	mutex;
	bool			grabbed;
}	t_fork;

typedef struct s_phil
{
	u8		id;
	t_fork	left;
	t_fork	right;
}	t_phil;

typedef struct s_timestamp
{
	u64				value;
	pthread_mutex_t	mutex;
}	t_timestamp;

#endif
