/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:21:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/09 17:18:17 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

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

size_t	lst_list_size(t_node *lst)
{
	unsigned int	len;

	if (!lst)
		return (0);
	while (lst->prev)
		lst = lst->prev;
	len = 1;
	while (lst->next)
	{
		lst = lst->next;
		len++;
	}
	return (len);
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

t_node	*input_parse(char const **argv, int argc)
{
	char			***split;
	t_node			*tmp;
	unsigned int	i;
	unsigned int	j;

	if (argc < 2 || !input_valid_check((char **)argv))
		return (NULL);
	split = super_split((char const **)argv, argc);
	if (!split)
		return (NULL);
	tmp = NULL;
	j = 0;
	while (split[j])
	{
		i = 0;
		while (split[j][i])
			if (!lst_add_back(&tmp, lst_node_new(ft_atoi(split[j][i++]), 0)))
				return (free_all(split), lst_clear_full(&tmp), NULL);
		j++;
	}
	free_all(split);
	return (tmp);
}
