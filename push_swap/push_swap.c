/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/04 23:33:02 by vvobis           ###   ########.fr       */
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

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
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

int	lst_check_sort(LIST *stack, unsigned int off)
{
	while (stack && stack->next)
	{
		if (*(int *)((char *)stack + off) > *(int *)((char *)stack->next + off))
			return (0);
		stack = stack->next;
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
	lst_list_memset(input, INCREASE, 0, 0);
	lst_list_sort_by_offset(input, 4);
}

void	debug_print(LIST *stack_a, LIST *stack_b)
{
	ft_printf("\nStack A\n");
	db_lst_menu(stack_a, PRINT_TO_END, 1, 2, "Node value", 0);
	ft_printf("\nStack B\n");
	db_lst_menu(stack_b, PRINT_TO_END, 1, 2, "Node value", 0);
}

int	lst_get_extreme_information(LIST *node, enum_memb extreme, unsigned int offset)
{
	int i;

	i = 0;
	if (!node)
		return (-1);
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
	if (!node)
		return (-1);
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (*(int *)((char *)node + offset) == value)
			return (i);
		node = node->next;
		i++;
	}
	return (-1);
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

int	input_sort_three(LIST **stack_a, void (**op)(LIST **, LIST **))
{
	int	a;
	int b;
	int c;

	a = *(int *)(*stack_a);
	b = *(int *)((*stack_a)->next);
	c = *(int *)((*stack_a)->next->next);

	if (a > b && b < c && a > c)
		return (op[RA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a > b && b < c && c > a)
		return (op[SA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a > b && b > c)
		return (op[SA](stack_a, NULL), op[RRA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a < b && b > c && c > a)
		return (op[SA](stack_a, NULL), op[RA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a < b && c < a)
		return (op[RRA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	return (1);
}

int		next_number_in_chunk_position(LIST *stack, int chunk_range[3], int *current_value)
{
	int value_counter;
	int	number_found;
	int	next_pos;
	int	return_pos[2];

	number_found = -1;
	value_counter = chunk_range[0];
	return_pos[0] = stack->size / 2;
	return_pos[1] = stack->size / 2;
	while (value_counter <= chunk_range[1])
	{
		next_pos = lst_node_get_absolute_position(stack, 0, value_counter);
		if (next_pos != -1)
		{
			if (next_pos < return_pos[0])
				number_found = 0;
			else if (next_pos > return_pos[1])
				number_found = 1;
			else
			{
				value_counter++;
				continue ;
			}
			*current_value = value_counter;
			return_pos[number_found] = next_pos;
		}
		value_counter++;
	}
	if (number_found != -1)
	{
		if (return_pos[0] > (int)stack->size - return_pos[1])
			return (return_pos[1]);
		else
			return (return_pos[0]);
	}
	return (-1);
}

int		find_rotation(LIST *stack, int current_value)
{
	int rotation;

	rotation = lst_node_get_absolute_position(stack, 0, current_value);
	if (rotation > (int)stack->size / 2)
		return (0);
	return (1);
}

void	problem_solve(LIST **stack_a, LIST **stack_b, ssize_t *count)
{
	int		next_pos;
	int		current_value;
	void	(**operation)(LIST **, LIST **);
	int		chunker[3];

	*count = 0;
	chunker[0] = 0;
	chunker[1] = (*stack_a)->size / 5;
	chunker[2] = chunker[1];
	operation = operations_initialize();
	while (*stack_a)
	{
		current_value = 0;
		next_pos = next_number_in_chunk_position(*stack_a, chunker, &current_value);
		if (next_pos == -1)
		{
			chunker[0] = chunker[1];
			chunker[1] += chunker[2];
			continue ;
		}
		if (next_pos > ((int)(*stack_a)->size / 2))
			while ((*stack_a)->value != current_value)
				operation[RRA](stack_a, NULL);
		else
			while ((*stack_a)->value != current_value)
				operation[RA](stack_a, NULL);
		current_value = lst_get_extreme_information(*stack_b, MAXIMUM, 0);
		if (*stack_b && current_value != -1)
		{
			if (current_value < (*stack_a)->value)
			{
				current_value = lst_get_extreme_information(*stack_b, MINIMUM, 0);
				next_pos = lst_node_get_absolute_position(*stack_b, 0, current_value);
				if (next_pos > (int)(*stack_b)->size / 2)
					while ((*stack_b)->value != current_value)
						operation[RRB](stack_b, NULL);
				else
					while ((*stack_b)->value != current_value)
						operation[RB](stack_b, NULL);
			}
			else
			{
				current_value = lst_get_extreme_information(*stack_b, MAXIMUM, 0);
				if (current_value > (*stack_a)->value)
				{
					next_pos = lst_node_get_absolute_position(*stack_b, 0, current_value);
					if (next_pos > (int)(*stack_b)->size / 2)
						while ((*stack_b)->value != current_value)
							operation[RRB](stack_b, NULL);
					else
						while ((*stack_b)->value != current_value)
							operation[RB](stack_b, NULL);
				}
			}
		}
		operation[PB](stack_a, stack_b);
		if ((*stack_a)->size == 1)
		{
			operation[PB](stack_a, stack_b);
			break ;
		}
	}
	return ;
	current_value = (*stack_b)->size - 1;
	while (*stack_b)
	{
		if (find_rotation(*stack_b, current_value))
			while ((*stack_b)->value != current_value)
				operation[RB](stack_b, NULL);
		else
			while ((*stack_b)->value != current_value)
				operation[RRB](stack_b, NULL);
		operation[PA](stack_a, stack_b);
		current_value--;
	}
	free(operation);
}

int	main(int argc, char **argv)
{
	LIST	*stack_a;
	LIST	*stack_b;
	ssize_t	count;

	if (argc < 2 || !input_valid_check(argv + 1))
		exit(-1);
	stack_a = input_parse((char const **)argv + 1, argc);
	stack_b = NULL;
	count = 1;
	input_normalize(&stack_a);
	problem_solve(&stack_a, &stack_b, &count);
	debug_print(stack_a, stack_b);
	//ft_printf("%d\n", count);
	lst_clear_full(&stack_a);
	lst_clear_full(&stack_b);
	return (0);
}
