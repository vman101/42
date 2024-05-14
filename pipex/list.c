/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:44:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/14 20:14:33 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_clean	*lst_node_new(void *content, void (*del)(void *))
{
	t_clean	*new;

	if (!content || !del)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = content;
	new->clean = del;
	new->next = NULL;
	return (new);
}

void	lst_node_del(t_clean **lst)
{
	if (!lst || !*lst)
		return ;
	(*lst)->clean((*lst)->content);
	free(*lst);
	*lst = NULL;
}

void	lst_list_clean(t_clean **head)
{
	t_clean	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		lst_node_del(head);
		*head = NULL;
		*head = tmp;
	}
	free(*head);
}

int	lst_add_back(t_clean **node, t_clean *new)
{
	t_clean	*tmp;

	if (!new)
	{
		perror("malloc");
		return (0);
	}
	if (*node)
	{
		tmp = *node;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*node = new;
	return (1);
}
