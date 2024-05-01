/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:44:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/01 11:50:12 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

node_t	*lst_node_new(int value, int index)
{
	node_t	*new;
	
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = index;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_node_add_front(node_t **node, node_t *new)
{
	node_t *tmp;

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

void	lst_node_add_back(node_t **node, node_t *new)
{
	node_t	*tmp;

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

node_t	*lst_node_last(node_t *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	lst_node_del(node_t **lst)
{
	if (*lst && (*lst)->prev && (*lst)->next)
	{
		(*lst)->prev->next = (*lst)->next;
		(*lst)->next->prev = (*lst)->prev;
	}
	free(*lst);
	*lst = NULL;
}

void	lst_clear_to_end(node_t **head)
{
	node_t *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void	lst_clear_full(node_t **head)
{
	if (!*head)
		return ;
	while ((*head)->prev)
		(*head) = (*head)->prev;
	lst_clear_to_end(head);
}
