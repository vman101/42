/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:21:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/04 19:44:34 by vvobis           ###   ########.fr       */
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

size_t	lst_list_size(LIST *lst)
{
	unsigned int	len;

	if (!lst)
		return (0);
	while (lst->prev)
		lst = lst->prev;
	len = 1;
	while(lst->next)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

char ***super_split(char const **argv, int argc)
{
	char ***split;
	unsigned int i;

	split = ft_calloc(argc, sizeof(*split));
	i = 0;
	while (*argv)
	{
		split[i++] = ft_split(*argv++, 32);
		if (!split[i - 1])
			return (NULL);
	}
	split[i] = NULL;
	return (split);
}

LIST	*input_parse(char const **argv, int argc)
{
	char	***split;
	LIST	*tmp;
	unsigned int	index;
	unsigned int	i;
	unsigned int	j;

	split = super_split(argv, argc);
	if (!split)
		return (NULL);
	tmp = NULL;
	j = 0;
	index = 0;
	while (split[j])
	{
		i = 0;
		while (split[j][i])
		{
			lst_node_add_back(&tmp, lst_node_new(ft_atoi(split[j][i]), index++));
			i++;
		}
		j++;
	}
	while (tmp->prev)
		tmp = tmp->prev;
	tmp->size = lst_list_size(tmp);
	lst_list_information_sync(tmp, offsetof(LIST, size));
	free_all(split);
	return (tmp);
}
