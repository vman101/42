/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:44:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/28 14:55:13 by vvobis           ###   ########.fr       */
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

void	lst_node_del(node_t *lst)
{
	if (lst && lst->prev)
		lst->prev->next = lst->next;
	free(lst);
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
	while ((*head)->prev)
		(*head) = (*head)->prev;
	lst_clear_to_end(head);
}
