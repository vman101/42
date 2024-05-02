/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/02 21:36:38 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"
#include <stdio.h>

void move_cursor(unsigned int rows, unsigned int cols)
{
	printf("\033[%d;%dH", rows, cols);	
}

int	input_valid_check(char **argv)
{
	unsigned int i;
	unsigned int j;

	j = 0;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (!ft_isdigit(argv[j][i]) && argv[j][i] != 32)
				return (0);
			i++;
		}
		j++;
	}
	return (1);
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

int	lst_check_sort(node_t *head, unsigned int offset)
{
	while (head && head->next)
	{
		if ((int)*(char *)head + offset > (int)*(char *)(head->next) + offset)
			return (0);
		head = head->next;
	}
	return (1);
}

void	input_sort_by_index(node_t **input)
{
	node_t	*tmp;
	node_t	*current;

	tmp = *input;
	while (!lst_check_sort(tmp, 4))
	{
		current = tmp;
		while (current && current->next)
		{
			if (current->index > current->next->index)
				lst_node_swap(current, current->next);
			current = current->next;
		}
	}
}

void	input_sort_by_value(node_t *input)
{
	node_t	*tmp;
	node_t	*current;
	unsigned int	i;

	tmp = input;
	while (!lst_check_sort(tmp, 0))
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
		tmp->value = i++;
		tmp = tmp->next;
	}
	input_sort_by_index(&input);
}

void	debug_print(node_t *head_a, node_t *head_b)
{
	ft_printf("\033[2J\033[H");
	ft_printf("\nStack A\n");
	db_lst_menu(head_a, PRINT_TO_END, 3, 6, "Node value", offsetof(node_t, value), "Node index", offsetof(node_t, index), "List Size", offsetof(node_t, size));
	ft_printf("\nStack B\n");
	db_lst_menu(head_b, PRINT_TO_END, 3, 6, "Node value", offsetof(node_t, value), "Node index", offsetof(node_t, index), "List Size", offsetof(node_t, size));
}

void	visual(node_t **head_a, node_t **head_b)
{
	while (1)
	{
		char c = 0;
		debug_print(*head_a, *head_b);
		read(STDIN_FILENO, &c, 1);
		switch (c)
		{
			case 'a':
				ra(head_a);
				break ;
			case 'b':
				rb(head_b);
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
				rra(head_a);
				break ;
			case 'd':
				rrb(head_b);
				break ;
			case 'o':
				rrr(head_a, head_b);
				break ;
			case 't':
				sa(head_a);
				break ;
			case 'z':
				sb(head_b);
				break ;
			case 'l':
				ss(head_a, head_b);
				break ;
			default:
				break ;
		}
		debug_print(*head_a, *head_b);
		if (c == '1')
			break ;
	}
}

void	problem_solve(node_t *head_a, node_t *head_b, unsigned int *count)
{
	if (head_a->size < 3 && !lst_check_sort(head_a, 0))
	{
//		sa(&head_a);
		(*count)++;
		return ;
	}
	while (head_a->size > 3)
	{
		pb(&head_a, &head_b);
		(*count)++;
	}
}

int	main(int argc, char **argv)
{
	node_t	*head_a;
	node_t	*head_b;
	unsigned int	count;

	if (argc < 2 || !input_valid_check(argv + 1))
		exit(-1);
	head_a = input_parse((char const **)argv + 1, argc);
//	input_sort_by_value(head_a);
	head_b = NULL;
	count = 0;
//	problem_solve(head_a, head_b, &count);
	visual(&head_a, &head_b);
	lst_clear_full(&head_a);
	lst_clear_full(&head_b);
}
