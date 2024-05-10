/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:57:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/10 10:58:17 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**free_all(char ***back)
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

char	***super_split(char const **argv, int argc)
{
	char			***split;
	unsigned int	i;

	split = ft_calloc(argc, sizeof(*split));
	if (!split)
		return (NULL);
	i = 0;
	while (*argv)
	{
		split[i] = ft_split(*argv, 32);
		if (!split[i])
		{
			free_all(split);
			return (NULL);
		}
		i++;
		argv++;
	}
	return (split);
}

