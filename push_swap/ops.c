/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:44:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/01 11:50:30 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	s_a_b(node_t **head)
{
	if (!*head)
		return ;
	lst_node_swap((*head)->next, *head);
}

void	ss(node_t **head_a, node_t **head_b)
{
	if (!*head_a || !*head_b)
		return ;
	s_a_b(head_a);
	s_a_b(head_b);
}

void	r_a_b(node_t **head)
{
	node_t *last;
	node_t	*tmp;

	if (!*head)
		return ;
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
	if (!*head_a || !*head_b)
		return ;
	r_a_b(head_a);
	r_a_b(head_b);
}

void	rr_a_b(node_t **head)
{
	node_t *last;

	if (!*head)
		return ;
	last = lst_node_last(*head);
	last->prev->next = NULL;
	last->next = *head;
	(*head)->prev = last;
	last->prev = NULL;
	*head = (*head)->prev;
}

void	rrr(node_t **head_a, node_t **head_b)
{
	if (!*head_a || !*head_b)
		return ;
	rr_a_b(head_a);
	rr_a_b(head_b);
}

void	pa(node_t **head_a, node_t **head_b)
{
	if (!*head_b)
		return ;
	lst_node_add_front(head_a, lst_node_new((*head_b)->value, (*head_b)->index));
	if ((*head_b)->next)
	{
		*head_b = (*head_b)->next;
		lst_node_del(&(*head_b)->prev);
	}
	else
		lst_node_del(head_b);
}

void	pb(node_t **head_a, node_t **head_b)
{
	if (!*head_a)
		return ;
	lst_node_add_front(head_b, lst_node_new((*head_a)->value, (*head_a)->index));
	if ((*head_a)->next)
	{
		*head_a = (*head_a)->next;
		lst_node_del(&(*head_a)->prev);
	}
	else
		lst_node_del(head_a);
}
