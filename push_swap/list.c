/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:44:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/05 13:45:40 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

list	*lst_node_new(int value, int index)
{
	list	*new;
	
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = index;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_list_information_sync(list *lst, unsigned int offset)
{
	list *tmp;

	tmp = lst;
	while (tmp->next)
	{
		if (*(int *)((char *)tmp + offset) != *(int *)((char *)(tmp->next) + offset)) 
			*(int *)((char *)(tmp->next) + offset) = *(int *)((char *)tmp + offset);
		tmp = tmp->next;
	}
}

void	lst_node_add_front(list **node, list *new)
{
	list *tmp;

	if (!new)
		return ;
	if (*node)
	{
		tmp = *node;
		while (tmp->prev)
			tmp = tmp->prev;
		tmp->prev = new;
		new->next = tmp;
		*node = new;
		(*node)->prev = NULL;
	}
	else
		*node = new;
}

void	lst_node_add_back(list **node, list *new)
{
	list	*tmp;

	if (!new)
		return ;
	if (*node)
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*node = new;
}

list	*lst_node_last(list *head)
{
	if (head)
		while (head->next)
			head = head->next;
	return (head);
}

void	lst_node_del(list **lst)
{
	if (*lst && (*lst)->prev && (*lst)->next)
	{
		(*lst)->prev->next = (*lst)->next;
		(*lst)->next->prev = (*lst)->prev;
	}
	free(*lst);
	*lst = NULL;
}

void	lst_clear_to_end(list **head)
{
	list *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void	lst_clear_full(list **head)
{
	if (!*head)
		return ;
	while ((*head)->prev)
		(*head) = (*head)->prev;
	lst_clear_to_end(head);
}
