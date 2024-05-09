/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:20:20 by victor            #+#    #+#             */
/*   Updated: 2024/05/09 17:23:35 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

t_node	*lst_node_first(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->prev)
		node = node->prev;
	return (node);
}

void	lst_node_del(t_node **lst)
{
	if (*lst && (*lst)->prev && (*lst)->next)
	{
		(*lst)->prev->next = (*lst)->next;
		(*lst)->next->prev = (*lst)->prev;
	}
	free(*lst);
	*lst = NULL;
}

void	lst_clear_to_end(t_node **head)
{
	t_node	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void	lst_clear_full(t_node **head)
{
	if (!*head)
		return ;
	while ((*head)->prev)
		(*head) = (*head)->prev;
	lst_clear_to_end(head);
}

void	lst_list_information_sync(t_node *lst, unsigned int offset)
{
	t_node	*tmp;

	tmp = lst;
	while (tmp->next)
	{
		if (*(int *)((char *)tmp + offset) != \
				*(int *)((char *)(tmp->next) + offset))
			*(int *)((char *)(tmp->next) + offset) = \
				*(int *)((char *)tmp + offset);
		tmp = tmp->next;
	}
}
