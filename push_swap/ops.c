/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:44:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/02 21:39:04 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	sa(node_t **head)
{
	if (!*head)
		return ;
	lst_node_swap((*head)->next, *head);
	ft_printf("sa\n");
}

void	sb(node_t **head)
{
	if (!*head)
		return ;
	lst_node_swap((*head)->next, *head);
	ft_printf("sb\n");
}

void	ss(node_t **head_a, node_t **head_b)
{
	if (!*head_a || !*head_b)
		return ;
	sa(head_a);
	sb(head_b);
	ft_printf("ss\n");
}

void	ra(node_t **head)
{
	node_t	*last;
	node_t	*tmp;

	if (!*head)
		return ;
	ft_printf("ra\n");
	if ((*head)->next || (*head)->prev)
	{
		tmp = (*head)->next;
		(*head)->next->prev = NULL;
		last = lst_node_last(*head);
		(*head)->prev = last;
		last->next = *head;
		(*head)->next = NULL;
		*head = tmp;
	}
	else
		return ;
}

void	rb(node_t **head)
{
	node_t	*last;
	node_t	*tmp;

	if (!*head)
		return ;
	ft_printf("rb\n");
	if ((*head)->next || (*head)->prev)
	{
		tmp = (*head)->next;
		(*head)->next->prev = NULL;
		last = lst_node_last(*head);
		(*head)->prev = last;
		last->next = *head;
		(*head)->next = NULL;
		*head = tmp;
	}
	else
		return ;
}

void	rr(node_t **head_a, node_t **head_b)
{
	ra(head_a);
	rb(head_b);
	ft_printf("rr\n");
}

void	rra(node_t **head)
{
	node_t	*last;
	node_t	*tmp;

	if (!*head)
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

void	rrb(node_t **head)
{
	node_t	*last;

	if (!*head)
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

void	rrr(node_t **head_a, node_t **head_b)
{
	rra(head_a);
	rrb(head_b);
	ft_printf("rrr\n");
}

void	pb(node_t **head_a, node_t **head_b)
{
	node_t	*tmp;

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
		return ;
	}
	tmp->next = *head_b;
	(*head_b)->prev = tmp;
	*head_b = tmp;

}

void	pa(node_t **head_a, node_t **head_b)
{
	node_t	*tmp;

	if (!*head_b)
		return ;
	ft_printf("pa\n");
	tmp = *head_b;
	*head_b = (*head_b)->next;
	if (*head_b)
	{
		(*head_b)->prev = NULL;
		(*head_b)->size -= 1;
	}
	if (!*head_a)
	{
		tmp->next = NULL;
		tmp->prev = NULL;
		*head_a = tmp;
		return ;
	}
	tmp->next = *head_a;
	(*head_a)->prev = tmp;
	*head_a = tmp;
	(*head_a)->size += 1;
}
