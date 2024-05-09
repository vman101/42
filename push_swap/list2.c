/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:34:59 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/09 17:23:12 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	lst_node_swap(t_node *n1, t_node *n2)
{
	int	value;
	int	index;

	value = n1->value;
	index = n1->index;
	n1->value = n2->value;
	n1->index = n2->index;
	n2->value = value;
	n2->index = index;
}

t_node	*lst_node_extract(t_node *node, int offset_value, int value)
{
	if (!node)
		return (NULL);
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (*(int *)((char *)node + offset_value) == value)
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	lst_check_sort(t_node *stack, unsigned int off)
{
	while (stack && stack->next)
	{
		if (*(int *)((char *)stack + off) > *(int *)((char *)stack->next + off))
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	lst_list_sort_by_offset(t_node **input, unsigned int offset)
{
	t_node	*tmp;
	t_node	*current;

	tmp = *input;
	while (!lst_check_sort(tmp, offset))
	{
		current = tmp;
		while (current && current->next)
		{
			if (*(int *)((char *)current + offset) > \
				*(int *)((char *)current->next + offset))
				lst_node_swap(current, current->next);
			current = current->next;
		}
	}
}

void	lst_list_memset(t_node **lst, t_enum_memb option, \
						unsigned int offset, int value)
{
	t_node	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*(int *)((char *)tmp + offset) = value;
		if (option == INCREASE)
			value++;
		tmp = tmp->next;
	}
}
