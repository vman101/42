/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:21:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/02 16:32:39 by vvobis           ###   ########.fr       */
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
char	**free_all(char ***back)
{
	char	***tmp;

	tmp = back;
	while (*back)
	{
		while (**back)
		{
			free(**back);
			(*back)++;
		}
		free(*back);
		back++;
	}
	free(tmp);
	return (NULL);
}

unsigned int	lst_list_size(node_t *lst)
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
	char ***split_back;

	split = ft_calloc(argc, sizeof(*split));
	split_back = split;
	while (*argv)
	{
		*split = ft_split(*argv, 32);
		split++;
		argv++;
	}
	split = NULL;
	return (split_back);
}

node_t	*input_parse(char const **argv, int argc)
{
	char	***split;
	char	***split_free;
	node_t	*tmp;
	unsigned int	i;

	split = super_split(argv, argc);
	if (!split)
		return (NULL);
	tmp = NULL;
	split_free = split;
	i = 1;
	while (*split)
	{
		while (**split)
		{
			lst_node_add_back(&tmp, lst_node_new(ft_atoi(**split), i++));
			(*split)++;
		}
		split++;
	}
	tmp->size = lst_list_size(tmp);
	lst_list_information_sync(tmp, offsetof(node_t, size));
	db_lst_menu(tmp, PRINT_FULL, 1, 2, "Node Value", offsetof(node_t, value));
	free_all(split_free);
	return (tmp);
}
