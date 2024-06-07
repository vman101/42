/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:21:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/31 12:57:33 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libft.h"

void	*free_super_split(char ***back)
{
	char	***free_back;
	char	**tmp;

	if (!back)
		return (NULL);
	free_back = back;
	while (*back)
	{
		tmp = *back;
		while (*tmp)
		{
			free(*tmp);
			*tmp = NULL;
			tmp++;
		}
		free(*back);
		*back = NULL;
		back++;
	}
	free(free_back);
	free_back = NULL;
	return (NULL);
}

void	free_split(char **split)
{
	char	**back;

	back = split;
	while (*back)
	{
		free(*back);
		*back = NULL;
		back++;
	}
	free(split);
}

char	***super_split(char **strs, int size, int delimiter)
{
	char			***split;
	unsigned int	i;

	split = ft_calloc(size, sizeof(*split));
	if (!split)
		return (NULL);
	i = 0;
	while (*strs)
	{
		split[i] = ft_split(*strs, delimiter);
		if (!split[i])
		{
			free_super_split(split);
			return (NULL);
		}
		i++;
		strs++;
	}
	split[i] = NULL;
	return (split);
}
