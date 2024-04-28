/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/28 14:30:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	lst_node_swap(node_t *n1, node_t *n2)
{
	node_t tmp;

    tmp.value = n1->value;
    n1->value = n2->value;
    n2->value = tmp.value;
}

int	lst_check_sort(node_t *head)
{
	while (head && head->next)
	{
		if (head->value > head->next->value)
			return (0);
		head = head->next;
	}
	return (1);
}

void	input_sort(node_t *input)
{
	node_t	*tmp;
	node_t	*current;

	tmp = input;
	while (!lst_check_sort(tmp))
	{
		current = tmp;
		while (current && current->next)
		{
			if (current->value > current->next->value)
				lst_node_swap(current, current->next);
			current = current->next;
		}
	}
}

int main(int argc, char **argv)
{
	node_t	*head;
	size_t	input_size;

	if (argc != 2)
		exit (-1);
	input_size = 0;
	head = input_parse(argv[1], &input_size);
	input_sort(head);
	db_lst_menu(head, PRINT_FULL, 2, 4, "Node value", offsetof(node_t, value), "Node index", offsetof(node_t, index));
	lst_clear_full(&head);
}
