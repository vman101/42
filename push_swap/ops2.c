/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:42:18 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 22:44:29 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	sa(list **head, list **null)
{
	null = NULL;
	if (!*head || null)
		return ;
	lst_node_swap((*head)->next, *head);
	ft_printf("sa\n");
}

void	sb(list **head, list **null)
{
	if (!*head || null)
		return ;
	lst_node_swap((*head)->next, *head);
	ft_printf("sb\n");
}

void	ss(list **head_a, list **head_b)
{
	if (!*head_a || !*head_b)
		return ;
	sa(head_a, NULL);
	sb(head_b, NULL);
	ft_printf("ss\n");
}

void	ra(list **head, list **null)
{
	list	*last;
	list	*tmp;

	if (!*head || null)
		return ;
	if ((*head)->next || (*head)->prev)
	{
		ft_printf("ra\n");
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

void	rb(list **head, list **null)
{
	list	*last;
	list	*tmp;

	if (!*head || null)
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

