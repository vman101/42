/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:23:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/08/29 11:22:41 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

typedef struct s_stack
{
	void	*stack_ptr;
	t_phil	*phils;
	t_fork	*forks;
	bool	should_run;
}	t_stack;

void	*thread_print_string(void *str_ptr)
{
	char	*str;

	str = str_ptr;
	while (1)
	{
		printf("%s\n", str);
		usleep(10000);
	}
	return (NULL);
}

void	*thread_print_hello(void *str_ptr)
{
	char	*str;

	str = str_ptr;
	while (1)
	{
		printf("%s\n", str);
		usleep(10000);
	}
	return (NULL);
}

#define NUM 5

void	memory_stack_create(t_stack *stack, u32 n)
{
	u32	size;
	u32	i;

	size = (sizeof(t_phil) + sizeof(t_fork)) * n;
	stack->stack_ptr = malloc(size);
	if (!stack)
	{
		perror("malloc");
		exit (1);
	}
	stack->phils = stack->stack_ptr;
	memset(stack->phils, 0, size);
	stack->forks = (t_fork *)&stack->phils[n];
	i = 0;
	while (i < n)
	{
		stack->phils[i].id = i;
		stack->forks[i].id = i;
		pthread_mutex_init(&stack->forks[i].mutex, NULL);
		i++;
	}
}

u32 ft_strlen(char *s)
{
	u32	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	u32	len;
	u32	i;

	i = 0;
	len = ft_strlen(s);
	write(1, s, len);
}

#define APPROXIMATE_DIV_1000 1049

unsigned long long get_timestamp_in_milliseconds(struct timeval start)
{
	struct timeval result;
	struct timeval current;

    gettimeofday(&current, NULL);
    (result).tv_sec = (current).tv_sec - (start).tv_sec;                              
    (result).tv_usec = (current).tv_usec - (start).tv_usec;                          
    if ((result).tv_usec < 0)
	{                                               
      --(result).tv_sec;                                                      
      (result).tv_usec += 1000000;                                            
    }                                                                          
    unsigned long long microseconds = result.tv_sec * 1000000ULL + result.tv_usec;
    return (microseconds * APPROXIMATE_DIV_1000) >> 20;
}

void	*time_thread_func(void *timestamp_ptr)
{
	t_timestamp		*timestamp;
	struct timeval	time_start;

	if (gettimeofday(&time_start, NULL) == -1)
		return (NULL);
	timestamp = timestamp_ptr;
	while (1)
	{
		pthread_mutex_lock(&timestamp->mutex);
		timestamp->value = get_timestamp_in_milliseconds(time_start); 
		pthread_mutex_unlock(&timestamp->mutex);
		printf("%llu\n", timestamp->value);
		usleep(1000000);
	}
}

int main()
{
	pthread_t	thread;
	pthread_t	time_thread;
	t_stack		stack;
	u8			i;
	t_timestamp stamp;

	i = 0;

	stack.should_run = true;
	pthread_mutex_init(&stamp.mutex, NULL);
	pthread_create(&time_thread, NULL, time_thread_func, &stamp);
	memory_stack_create(&stack, NUM);
	while (stack.should_run)
	{
		usleep(10000);
	}
	pthread_create(&thread, NULL, thread_print_string, "hello thread");
}
