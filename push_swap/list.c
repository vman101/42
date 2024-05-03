/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:44:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/03 12:17:46 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

LIST	*lst_node_new(int value, int index)
{
	LIST	*new;
	
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = index;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_list_information_sync(LIST *lst, unsigned int offset)
{
	LIST *tmp;

	tmp = lst;
	while (tmp->next)
	{
		if ((int)*(char *)tmp + offset != (int)*(char *)(tmp->next) + offset) 
			*(int *)((char *)(tmp->next) + offset) = (int)*((char *)tmp + offset);
		tmp = tmp->next;
	}
}

void	lst_node_add_front(LIST **node, LIST *new)
{
	LIST *tmp;

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

void	lst_node_add_back(LIST **node, LIST *new)
{
	LIST	*tmp;

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

LIST	*lst_node_last(LIST *head)
{
	if (head)
		while (head->next)
			head = head->next;
	return (head);
}

void	lst_node_del(LIST **lst)
{
	if (*lst && (*lst)->prev && (*lst)->next)
	{
		(*lst)->prev->next = (*lst)->next;
		(*lst)->next->prev = (*lst)->prev;
	}
	free(*lst);
	*lst = NULL;
}

void	lst_clear_to_end(LIST **head)
{
	LIST *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void	lst_clear_full(LIST **head)
{
	if (!*head)
		return ;
	while ((*head)->prev)
		(*head) = (*head)->prev;
	lst_clear_to_end(head);
}
