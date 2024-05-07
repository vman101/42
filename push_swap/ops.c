/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:44:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 22:43:42 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "swap.h"
void	pb(list **head_a, list **head_b)
{
	list	*tmp;

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
		stacks_update(head_a, head_b);
	}
	tmp->next = *head_b;
	(*head_b)->prev = tmp;
	*head_b = tmp;
	stacks_update(head_a, head_b);
}

void	pa(list **head_a, list **head_b)
{
	list	*tmp;

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
