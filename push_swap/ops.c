/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:44:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/28 16:20:57 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	s_a_b(node_t **head)
{
	lst_node_swap((*head)->next, *head);
}

void	ss(node_t **head_a, node_t **head_b)
{
	s_a_b(head_a);
	s_a_b(head_b);
}

void	r_a_b(node_t **head)
{
	node_t *last;

	(*head)->next->prev = NULL;
	last = lst_node_last(*head);
	(*head)->prev = last;
	last->next = *head;
	(*head)->next = NULL;
}

void	rr(node_t **head_a, node_t **head_b)
{
	r_a_b(head_a);
	r_a_b(head_b);
}

void	pa(node_t **head_a, node_t **head_b)
{
	(*head_b)->next = *head_a;
	(*head_a)->prev = *head_b;
	(*head_b)->prev = NULL;
}
