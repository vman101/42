/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:44:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/03 16:32:10 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	sa(LIST **head, LIST **null)
{
	null = NULL;
	if (!*head)
		return ;
	lst_node_swap((*head)->next, *head);
	ft_printf("sa\n");
}

void	sb(LIST **head, LIST **null)
{
	null = NULL;
	if (!*head)
		return ;
	lst_node_swap((*head)->next, *head);
	ft_printf("sb\n");
}

void	ss(LIST **head_a, LIST **head_b)
{
	if (!*head_a || !*head_b)
		return ;
	sa(head_a, NULL);
	sb(head_b, NULL);
	ft_printf("ss\n");
}

void	ra(LIST **head, LIST **null)
{
	LIST	*last;
	LIST	*tmp;

	null = NULL;
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

void	rb(LIST **head, LIST **null)
{
	LIST	*last;
	LIST	*tmp;

	null = NULL;
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

void	rr(LIST **head_a, LIST **head_b)
{
	ra(head_a, NULL);
	rb(head_b, NULL);
	ft_printf("rr\n");
}

void	rra(LIST **head, LIST **null)
{
	LIST	*last;
	LIST	*tmp;

	null = NULL;
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

void	rrb(LIST **head, LIST **null)
{
	LIST	*last;

	null = NULL;
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

void	rrr(LIST **head_a, LIST **head_b)
{
	rra(head_a, NULL);
	rrb(head_b, NULL);
	ft_printf("rrr\n");
}

void	pb(LIST **head_a, LIST **head_b)
{
	LIST	*tmp;

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
	lst_list_memset(head_a, NONE, offsetof(LIST, size), lst_list_size(*head_a));
	lst_list_memset(head_b, NONE, offsetof(LIST, size), lst_list_size(*head_b));
}

void	pa(LIST **head_a, LIST **head_b)
{
	LIST	*tmp;

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
		return ;
	}
	tmp->next = *head_a;
	(*head_a)->prev = tmp;
	*head_a = tmp;
	lst_list_memset(head_a, NONE, offsetof(LIST, size), lst_list_size(*head_a));
	lst_list_memset(head_b, NONE, offsetof(LIST, size), lst_list_size(*head_b));
}
