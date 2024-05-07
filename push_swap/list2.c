/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:34:59 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 22:36:23 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	lst_node_swap(list *n1, list *n2)
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

list	*lst_node_extract(list *node, int offset_value, int value)
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

int	lst_check_sort(list *stack, unsigned int off)
{
	while (stack && stack->next)
	{
		if (*(int *)((char *)stack + off) > *(int *)((char *)stack->next + off))
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	lst_list_sort_by_offset(list **input, unsigned int offset)
{
	list	*tmp;
	list	*current;

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

void	lst_list_memset(list **lst, enum_memb option, \
						unsigned int offset, int value)
{
	list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*(int *)((char *)tmp + offset) = value;
		if (option == INCREASE)
			value++;
		tmp = tmp->next;
	}
}
