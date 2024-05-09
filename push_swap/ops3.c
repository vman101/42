/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:43:29 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/09 17:27:56 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	rr(t_node **head_a, t_node **head_b)
{
	t_node	*last;
	t_node	*tmp;

	if (*head_a && *head_b && \
			((*head_a)->next || (*head_a)->prev))
	{
		tmp = (*head_a)->next;
		(*head_a)->next->prev = NULL;
		last = lst_node_last(*head_a);
		(*head_a)->prev = last;
		last->next = *head_a;
		(*head_a)->next = NULL;
		*head_a = tmp;
		tmp = (*head_b)->next;
		(*head_b)->next->prev = NULL;
		last = lst_node_last(*head_b);
		(*head_b)->prev = last;
		last->next = *head_b;
		(*head_b)->next = NULL;
		*head_b = tmp;
	}
	else
		return ;
	ft_printf("rr\n");
}

void	rra(t_node **head, t_node **null)
{
	t_node	*last;
	t_node	*tmp;

	if (!*head || null)
		return ;
	last = lst_node_last(*head);
	if (!last->prev)
		return ;
	tmp = last->prev;
	tmp->next = NULL;
	if (last->prev)
		last->prev->next = NULL;
	last->prev = NULL;
	last->next = *head;
	(*head)->prev = last;
	*head = last;
	ft_printf("rra\n");
}

void	rrb(t_node **head, t_node **null)
{
	t_node	*last;

	if (!*head || null)
		return ;
	last = lst_node_last(*head);
	last->prev->next = NULL;
	last->prev = NULL;
	(*head)->prev = last;
	last->next = *head;
	*head = last;
	(*head)->prev = NULL;
	ft_printf("rrb\n");
}

void	rrr(t_node **head_a, t_node **head_b)
{
	t_node	*last;
	t_node	*tmp;

	if (!*head_a || !*head_b)
		return ;
	last = lst_node_last(*head_a);
	if (!last->prev)
		return ;
	tmp = last->prev;
	tmp->next = NULL;
	if (last->prev)
		last->prev->next = NULL;
	last->prev = NULL;
	last->next = *head_a;
	(*head_a)->prev = last;
	*head_a = last;
	last = lst_node_last(*head_b);
	last->prev->next = NULL;
	last->prev = NULL;
	(*head_b)->prev = last;
	last->next = *head_b;
	*head_b = last;
	(*head_b)->prev = NULL;
	ft_printf("rrr\n");
}

void	stacks_update(t_node **stack_a, t_node **stack_b)
{
	if (*stack_a)
	{
		lst_list_memset(stack_a, NONE, 8, \
		lst_list_size(*stack_a));
		lst_list_memset(stack_a, INCREASE, 4, 0);
	}
	if (*stack_b)
	{
		lst_list_memset(stack_b, NONE, 8, \
				lst_list_size(*stack_b));
		lst_list_memset(stack_b, INCREASE, 4, 0);
	}
}
