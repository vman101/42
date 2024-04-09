/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:14:20 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/07 18:11:49 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(char const *s, char const c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (*s != c)
		n = 1;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1))
			n++;
		i++;
		s++;
	}
	return (n);
}

int	count_sub(char const *s, char const c)
{
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

char	**free_all(char **back)
{
	while (*back)
		free(*back++);
	free(back);
	return (NULL);
}

char	**ft_split(char const *s, char const c)
{
	char	**tmp;
	char	**back;

	if (!s)
		return (NULL);
	tmp = malloc(sizeof(*tmp) * count(s, c) + 1);
	if (!tmp)
		return (NULL);
	if (!*s)
		*tmp = NULL;
	back = tmp;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			break ;
		*tmp = ft_substr(s, 0, count_sub(s, c));
		if (!*tmp)
			return (free_all(back));
		while (*s != c && *s)
			s++;
		tmp++;
	}
	tmp = NULL;
	return (back);
}
