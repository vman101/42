/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:21:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/26 22:25:34 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int	count(char const *s, char const c)
{
	int	n;

	n = 0;
	if (*s != c && *s)
		n = 1;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1))
			n++;
		s++;
	}
	return (n);
}

static char	**free_all(char **back)
{
	char	**tmp;

	tmp = back;
	while (*back)
	{
		free(*back);
		back++;
	}
	free(tmp);
	return (NULL);
}

int	*input_parse(char const *argv, int *input_len)
{
	char **split;
	char	**split_free;
	int *tmp;
	int *back;

	*input_len = count(argv, 32);
	split = ft_split(argv, 32);
	if (!split)
		return (NULL);
	split_free = split;
	tmp = malloc(sizeof(*tmp) * *input_len);
	if (!tmp)
		return (NULL);
	back = tmp;
	while (*split)
		*tmp++ = ft_atoi(*split++);
	free_all(split_free);
	return (back);
}
