/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/03 16:32:12 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"
#include <stdio.h>

void move_cursor(unsigned int rows, unsigned int cols)
{
	printf("\033[%d;%dH", rows, cols);	
}

void	screen_clear()
{
	ft_printf("\033[2J\033[H");
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

void	lst_node_swap(LIST *n1, LIST *n2)
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

int	lst_check_sort(LIST *head, unsigned int off)
{
	while (head && head->next)
	{
		if (*(int *)((char *)head + off) > *(int *)((char *)head->next + off))
			return (0);
		head = head->next;
	}
	return (1);
}

void	lst_list_sort_by_offset(LIST **input, unsigned int offset)
{
	LIST	*tmp;
	LIST	*current;

	tmp = *input;
	while (!lst_check_sort(tmp, offset))
	{
		current = tmp;
		while (current && current->next)
		{
			if (*(int *)((char *)current + offset) > \
				*(int *)((char *)current->next + offset))
				lst_node_swap(current, current->next);
			current = current->next;
		}
	}
}

void	lst_list_memset(LIST **lst, enum_memb option, unsigned int offset, int value)
{
	LIST *tmp;

	tmp = *lst;
	while (tmp)
	{
		*(int *)((char *)tmp + offset) = value;
		if (option == INCREASE)
			value++;
		tmp = tmp->next;
	}
}

void	input_normalize(LIST **input)
{
	lst_list_sort_by_offset(input, 0);
	lst_list_memset(input, INCREASE, 0, 1);
	lst_list_sort_by_offset(input, 4);
}

void	debug_print(LIST *head_a, LIST *head_b)
{
	ft_printf("\nStack A\n");
	db_lst_menu(head_a, PRINT_TO_END, 1, 2, "Node value", 0);
	ft_printf("\nStack B\n");
	db_lst_menu(head_b, PRINT_TO_END, 1, 2, "Node value", 0);
}

int	lst_get_extreme_information(LIST *node, enum_memb extreme, unsigned int offset)
{
	int i;

	i = 0;
	while (node->prev)
		node = node->prev;
	if (extreme == MAXIMUM)
	{
		while (node->next)
		{
			if (i < *(int *)((char *)node + offset))
				i = *(int *)((char *)node + offset);
			node = node->next;
		}
	}
	else if (extreme == MINIMUM)
	{
		while (node->next)
		{
			if (i > *(int *)((char *)node + offset))
				i = *(int *)((char *)node + offset);
			node = node->next;
		}
	}
	return (i);
}

int	lst_node_get_absolute_position(LIST *node, unsigned int offset, int value)
{
	int i;

	i = 0;
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (*(int *)((char *)node + offset) == value)
			return (i);
		node = node->next;
		i++;
	}
	return (0);
}

void	(**operations_initialize(void))(LIST **, LIST **)
{
	void (**tmp)(LIST **, LIST **);

	tmp = malloc(sizeof(void (*)(LIST **, LIST **)) * 11);
	if (!tmp)
		return (NULL);
    tmp[0] = ra;
    tmp[1] = rb;
    tmp[2] = rr;
    tmp[3] = sa;
    tmp[4] = sb;
    tmp[5] = ss;
    tmp[6] = rra;
    tmp[7] = rrb;
    tmp[8] = rrr;
    tmp[9] = pa;
    tmp[10] = pb;
	return (tmp);
}

void	problem_solve(LIST **head_a, LIST **head_b, unsigned int *count)
{
	int				current_value;
	unsigned int	next_pos;
	void			(**operation)(LIST **, LIST **);
	LIST			*stack_current;

	operation = operations_initialize();
	while ((*head_a)->size > 3)
		operation[PB](head_a, head_b);
	while (*head_b)
	{
		stack_current = *head_a;
		current_value = stack_current->value;
		next_pos = lst_node_get_absolute_position(stack_current, 0, current_value - 1);
		if (!next_pos)
		{
			current_value = stack_current->value;
			stack_current = *head_a;
			next_pos = lst_node_get_absolute_position(stack_current, 0, current_value + 1);
			if (!next_pos)
				operation[RR](head_a, head_b);
		}
		if (next_pos < (stack_current->size / 2) + 1)
			while (stack_current->value != current_value)
				operation[RB](&stack_current, NULL);
		else
			while (stack_current->value != current_value)
				operation[RRB](&stack_current, NULL);
		current_value++;
		(*count)++;
	}
}

int	main(int argc, char **argv)
{
	LIST	*head_a;
	LIST	*head_b;
	unsigned int	count;

	if (argc < 2 || !input_valid_check(argv + 1))
		exit(-1);
	head_a = input_parse((char const **)argv + 1, argc);
	head_b = NULL;
	count = 0;
	input_normalize(&head_a);
	problem_solve(&head_a, &head_b, &count);
//	visual(&head_a, &head_b);
	debug_print(head_a, head_b);
	//ft_printf("%d\n", count);
	lst_clear_full(&head_a);
	lst_clear_full(&head_b);
}
