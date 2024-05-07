/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:44:55 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 10:54:18 by victor           ###   ########.fr       */
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

void	rr(list **head_a, list **head_b)
{
	list	*last;
	list	*tmp;

	if (!*head_a)
		return ;
	if ((*head_a)->next || (*head_a)->prev)
	{
		tmp = (*head_a)->next;
		(*head_a)->next->prev = NULL;
		last = lst_node_last(*head_a);
		(*head_a)->prev = last;
		last->next = *head_a;
		(*head_a)->next = NULL;
		*head_a = tmp;
	}
	else
		return ;

	if (!*head_b)
		return ;
	if ((*head_b)->next || (*head_b)->prev)
	{
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

void	rra(list **head, list **null)
{
	list	*last;
	list	*tmp;

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

void	rrb(list **head, list **null)
{
	list	*last;

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

void	rrr(list **head_a, list **head_b)
{
	list	*last;
	list	*tmp;

	if (!*head_a)
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
	if (!*head_b)
		return ;
	last = lst_node_last(*head_b);
	last->prev->next = NULL;
	last->prev = NULL;
	(*head_b)->prev = last;
	last->next = *head_b;
	*head_b = last;
	(*head_b)->prev = NULL;
	ft_printf("rrr\n");
}

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
		lst_list_memset(head_a, NONE, offsetof(list, size), lst_list_size(*head_a));
		lst_list_memset(head_a, INCREASE, offsetof(list, index), 0);
		lst_list_memset(head_b, NONE, offsetof(list, size), lst_list_size(*head_b));
		lst_list_memset(head_b, INCREASE, offsetof(list, index), 0);
	}
	tmp->next = *head_b;
	(*head_b)->prev = tmp;
	*head_b = tmp;
	lst_list_memset(head_a, NONE, offsetof(list, size), lst_list_size(*head_a));
	lst_list_memset(head_a, INCREASE, offsetof(list, index), 0);
	lst_list_memset(head_b, NONE, offsetof(list, size), lst_list_size(*head_b));
	lst_list_memset(head_b, INCREASE, offsetof(list, index), 0);
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
		lst_list_memset(head_a, NONE, offsetof(list, size), lst_list_size(*head_a));
		lst_list_memset(head_a, INCREASE, offsetof(list, index), 0);
		lst_list_memset(head_b, NONE, offsetof(list, size), lst_list_size(*head_b));
		lst_list_memset(head_b, INCREASE, offsetof(list, index), 0);
		return ;
	}
	tmp->next = *head_a;
	(*head_a)->prev = tmp;
	*head_a = tmp;
	lst_list_memset(head_a, NONE, offsetof(list, size), lst_list_size(*head_a));
	lst_list_memset(head_a, INCREASE, offsetof(list, index), 0);
	lst_list_memset(head_b, NONE, offsetof(list, size), lst_list_size(*head_b));
	lst_list_memset(head_b, INCREASE, offsetof(list, index), 0);
}
