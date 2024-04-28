/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:44:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/28 14:59:27 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	s_a_b(node_t **head)
{
	lst_node_swap(head->next, head);
}

void	ss(node_t **head_a, node_t **head_b)
{
	s_a_b(head_a);
	s_a_b(head_b);
}

void	r_a_b(node_t **head)
{
	lst_node_last(*head)->next = *head;
	(*head)->prev = *head;
	head->next = head->next-next;
}
