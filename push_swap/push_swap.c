/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/01 12:08:01 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"
#include <stdio.h>

void move_cursor(unsigned int rows, unsigned int cols)
{
	printf("\033[%d;%dH", rows, cols);	
}

void	lst_node_swap(node_t *n1, node_t *n2)
{
	int value;
	int index;

    value = n1->value;
	index = n1->index;
    n1->value = n2->value;
	n1->index = n2->index;
    n2->value = value;
	n2->index = index;

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

void	input_sort_and_index(node_t *input)
{
	node_t	*tmp;
	node_t	*current;
	unsigned int	i;

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
	i = 1;
	while (tmp)
	{
		tmp->index = i++;
		tmp = tmp->next;
	}
}

void	input_copy_indexes(node_t *a, node_t *a_sorted)
{
	node_t *tmp;

	tmp = a_sorted;
	while (a && a_sorted)
	{
		if (a->value == a_sorted->value)
		{
			a->index = a_sorted->index;
			a = a->next;
		}
		if (!a_sorted->next)
			a_sorted = tmp;
		else
			a_sorted = a_sorted->next;
	}
}

void	debug_print(node_t *head_a, node_t *head_b)
{
	ft_printf("\033[2J\033[H");
	ft_printf("\nStack A\n");
	db_lst_menu(head_a, PRINT_TO_END, 2, 4, "Node value", offsetof(node_t, value), "Node index", offsetof(node_t, index));
	ft_printf("\nStack B\n\n");
	db_lst_menu(head_b, PRINT_TO_END, 2, 4, "Node value", offsetof(node_t, value), "Node index", offsetof(node_t, index));
}

void	visual(node_t **head_a, node_t **head_b)
{
	while (1)
	{
		char c = 0;
		read(STDIN_FILENO, &c, 1);
		switch (c)
		{
			case 'a':
				r_a_b(head_a);
				break ;
			case 'b':
				r_a_b(head_b);
				break ;
			case 'r':
				rr(head_a, head_b);
				break ;
			case 'p':
				pa(head_a, head_b);
				break ;
			case 'q':
				pb(head_a, head_b);
				break ;
			case 'g':
				rr_a_b(head_a);
				break ;
			case 'd':
				rr_a_b(head_b);
				break ;
			case 'o':
				rrr(head_a, head_b);
				break ;
			case 't':
				s_a_b(head_a);
				break ;
			case 'z':
				s_a_b(head_b);
				break ;
			case 'l':
				ss(head_a, head_b);
				break ;
			default:
				break ;
		}
		if (c == '1')
			break ;
	}
}

int main(int argc, char **argv)
{
	node_t	*head_a;
	node_t	*head_b;
	node_t	*head_a_sorted;

	if (argc != 2)
		exit (-1);
	head_a = input_parse(argv[1]);
	head_a_sorted = input_parse(argv[1]);
	input_sort_and_index(head_a_sorted);
	input_copy_indexes(head_a, head_a_sorted);
	head_b = NULL;
	lst_clear_full(&head_a);
	lst_clear_full(&head_b);
}
