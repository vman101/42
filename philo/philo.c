/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/31 18:41:26 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>

void	*print_test(void *msg)
{
	ft_printf("Hello, World! Im thread: %s\n", (char *)msg);
	char *c = ft_strdup("yesssssir");
	return (c);
}

void	*inc_c(void	*mutex)
{
	int i;

	i = 1000000;
	while (i-- > 0)
	{
		pthread_mutex_lock((pthread_mutex_t *)((t_mutex *)mutex)->mutex);
		((t_mutex *)mutex)->c++;
		pthread_mutex_unlock((pthread_mutex_t *)((t_mutex *)mutex)->mutex);
	}
	return (NULL);
}

int main()
{
	pthread_t	*t;
	t_mutex		mutex;
	pthread_mutex_t	m;
	int				c;
	int				i;

	i = 0;
	t = ft_calloc(1, sizeof(*t));
	c = 0;
	pthread_mutex_init(&m, NULL);
	mutex.mutex = &m;
	mutex.c = &c;
	pthread_create(t, NULL, inc_c, &mutex);
	pthread_detach(*t);
	while (1)
	{
		pthread_mutex_lock(&m);
		ft_printf("%d\n", mutex.c);
		pthread_mutex_unlock(&m);
		usleep(50000);
	}
	free(t);
	return (0);
}
