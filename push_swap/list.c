/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:44:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/09 17:24:46 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"
#include <limits.h>

t_node	*lst_node_new(long value, int index)
{
	t_node	*new;

	if (value > INT_MAX || value < INT_MIN)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = (int)value;
	new->index = (int)index;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_node_add_front(t_node **node, t_node *new)
{
	t_node	*tmp;

	if (!new)
		return ;
	if (*node)
	{
		tmp = *node;
		while (tmp->prev)
			tmp = tmp->prev;
		tmp->prev = new;
		new->next = tmp;
		*node = new;
		(*node)->prev = NULL;
	}
	else
		*node = new;
}

int	lst_add_back(t_node **node, t_node *new)
{
	t_node	*tmp;

	if (!new)
		return (0);
	if (*node)
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*node = new;
	return (1);
}

t_node	*lst_node_last(t_node *head)
{
	if (head)
		while (head->next)
			head = head->next;
	return (head);
}
