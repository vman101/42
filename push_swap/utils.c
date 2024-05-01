/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:21:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/01 12:07:13 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

//static int	count(char const *s, char const c)
//{
//	int	n;
//
//	n = 0;
//	if (*s != c && *s)
//		n = 1;
//	while (*s)
//	{
//		if (*s == c && *(s + 1) != c && *(s + 1))
//			n++;
//		s++;
//	}
//	return (n);
//}
//
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

node_t	*input_parse(char const *argv)
{
	char	**split;
	char	**split_free;
	node_t	*tmp;

	split = ft_split(argv, 32);
	if (!split)
		return (NULL);
	tmp = NULL;
	split_free = split;
	while (*split)
		lst_node_add_back(&tmp, lst_node_new(ft_atoi(*split++), 0));
	while (tmp->prev)
		tmp = tmp->prev;
	free_all(split_free);
	return (tmp);
}
