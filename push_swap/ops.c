/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:44:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/09 17:15:52 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "swap.h"

void	pb(t_node **head_a, t_node **head_b)
{
	t_node	*tmp;

	if (!*head_a)
		return ;
	ft_printf("pb\n");
	tmp = *head_a;
	*head_a = (*head_a)->next;
	if (*head_a)
		(*head_a)->prev = NULL;
	if (!*head_b)
	{
		tmp->next = NULL;
		tmp->prev = NULL;
		*head_b = tmp;
		stacks_update(head_a, head_b);
		return ;
	}
	tmp->next = *head_b;
	(*head_b)->prev = tmp;
	*head_b = tmp;
	stacks_update(head_a, head_b);
}

void	pa(t_node **head_a, t_node **head_b)
{
	t_node	*tmp;

	if (!*head_b)
		return ;
	ft_printf("pa\n");
	tmp = *head_b;
	*head_b = (*head_b)->next;
	if (*head_b)
		(*head_b)->prev = NULL;
	if (!*head_a)
	{
		tmp->next = NULL;
		tmp->prev = NULL;
		*head_a = tmp;
		stacks_update(head_a, head_b);
		return ;
	}
	tmp->next = *head_a;
	(*head_a)->prev = tmp;
	*head_a = tmp;
	stacks_update(head_a, head_b);
}

void	stack_rotate(t_node *a[2], t_node **s_a, t_node **s_b, \
					void (**op)(t_node **a, t_node **b))
{
	while (a[0]->index)
	{
		if (a[1] && a[1]->index != 0 && a[1]->index > (*s_b)->size / 1 && \
			a[0]->index > (*s_b)->size / 2)
			op[RRR](s_a, s_b);
		else if (a[1] && a[1]->index != 0 && a[1]->index < (*s_b)->size / 2 && \
				a[0]->index < (*s_b)->size / 2)
			op[RR](s_a, s_b);
		else if (a[0]->index > (*s_a)->size / 2)
			op[RRA](s_a, NULL);
		else if (a[0]->index <= (*s_a)->size / 2)
			op[RA](s_a, NULL);
		stacks_update(s_a, s_b);
	}
}
