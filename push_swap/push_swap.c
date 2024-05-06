/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/06 12:26:56 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"
#include <stdio.h>

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

void	lst_node_swap(list *n1, list *n2)
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

int	lst_check_sort(list *stack, unsigned int off)
{
	while (stack && stack->next)
	{
		if (*(int *)((char *)stack + off) > *(int *)((char *)stack->next + off))
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	lst_list_sort_by_offset(list **input, unsigned int offset)
{
	list	*tmp;
	list	*current;

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

void	lst_list_memset(list **lst, enum_memb option, unsigned int offset, int value)
{
	list *tmp;

	tmp = *lst;
	while (tmp)
	{
		*(int *)((char *)tmp + offset) = value;
		if (option == INCREASE)
			value++;
		tmp = tmp->next;
	}
}

void	input_normalize(list **input)
{
	lst_list_sort_by_offset(input, 0);
	lst_list_memset(input, INCREASE, 0, 0);
	lst_list_sort_by_offset(input, 4);
}

void	debug_print(list *stack_a, list *stack_b)
{
	ft_printf("\nStack A\n");
	db_lst_menu(stack_a, PRINT_TO_END, 2, 4, "Node value", 0, "Node index", offsetof(list, index));
	ft_printf("\nStack B\n");
	db_lst_menu(stack_b, PRINT_TO_END, 2, 4, "Node value", 0, "Node index", offsetof(list, index));
}

int	lst_get_extreme_information(list *node, enum_memb extreme, unsigned int offset)
{
	int i;
	if (!node)
		return (-1);
	if (node->size == 0)
		return (0);
	if (extreme == MAXIMUM)
		i = 0;
	else
		i = 2147483647;
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (extreme == MAXIMUM)
		{
			if (i < *(int *)((char *)node + offset))
				i = *(int *)((char *)node + offset);
		}
		else if (extreme == MINIMUM)
		{
			if (i > *(int *)((char *)node + offset))
				i = *(int *)((char *)node + offset);
		}
		node = node->next;
	}
	return (i);
}

int	lst_node_get_absolute_position(list *node, enum_memb orientation, int offset_value, int offset_direction, int value)
{
	int i;

	i = 0;
	if (!node)
		return (-1);
	if (orientation == FRONT)
		while (node->prev)
			node = node->prev;
	else
		node = lst_node_last(node);
	while (node)
	{
		if (*(int *)((char *)node + offset_value) == value)
			return (i);
		 node = *(list **)((char *)node + offset_direction);
		i++;
	}
	return (-1);
}

void	(**operations_initialize(void))(list **a, list **b)
{
	void (**tmp)(list **a, list **b);

	tmp = malloc(sizeof(void (*)(list **, list **)) * 11);
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

int	input_sort_three(list **stack_a, void (**op)(list **, list **))
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

int		find_rotation(list *stack, int current_value)
{
	int front;
	int back;

	if (!stack)
		return (0);
	front = lst_node_get_absolute_position(stack, FRONT, 0, offsetof(list, next), current_value);
	back = lst_node_get_absolute_position(stack, BACK, 0, offsetof(list, prev), current_value);
	if (front <= back)
		return (front);
	return ((int)stack->size - back);
}

void	stacks_update(list **stack_a, list **stack_b)
{
	lst_list_memset(stack_a, NONE, offsetof(list, size), lst_list_size(*stack_a));
	lst_list_memset(stack_a, INCREASE, offsetof(list, index), 0);
	lst_list_memset(stack_b, NONE, offsetof(list, size), lst_list_size(*stack_b));
	lst_list_memset(stack_b, INCREASE, offsetof(list, index), 0);
}
int		next_number_in_chunk_position(list *stack, int chunk_range[3])
{
	int value_counter;
	int	test_pos;
	int	upper_pos;
	int lower_pos;

	value_counter = chunk_range[0];
	lower_pos = 0;
	upper_pos = stack->size;
	while (value_counter <= chunk_range[1])
	{
		test_pos = find_rotation(stack, value_counter);
		if (test_pos == -1 && lower_pos == 0 && upper_pos == (int)stack->size && value_counter == chunk_range[1])
			return (-1);
		if (test_pos >= 0 && test_pos < upper_pos)
			upper_pos = test_pos;
		else if (test_pos >= 0 && test_pos > lower_pos)
			lower_pos = test_pos;
		value_counter++;
	}
	if (upper_pos < ((int)stack->size - lower_pos))
		return (upper_pos);
	return (lower_pos);
}

int	find_best_spot(list *stack, int value)
{
	int	max;
	int min;
	int ex_plus;
	int ex_minus;
	int i;

	if (!stack)
		return (-1);
	max = lst_get_extreme_information(stack, MAXIMUM, 0);
	min = lst_get_extreme_information(stack, MINIMUM, 0);
	i = 0;
	if (max < value)
		return (find_rotation(stack, min));
	else if (min > value)
		return (find_rotation(stack, max));
	while (value + i < max && value - i > min)
	{
		ex_minus = find_rotation(stack, min + i);
		ex_plus = find_rotation(stack, max - i);
		if (ex_minus != -1)
			return (ex_minus + 2);
		else if (ex_plus != -1)
			return (ex_plus);
		i++;
	}
	return (-1);
}

void	problem_solve(list **stack_a, list **stack_b, ssize_t *count)
{
	int		next_pos;
	void	(**operation)(list **, list **);
	int		current_value;
	int		chunker[3];
	list	*tmp;

	*count = 0;
	chunker[0] = 0;
	chunker[1] = (*stack_a)->size / 11;
	chunker[2] = chunker[1];
	operation = operations_initialize();
	while (*stack_a)
	{
		stacks_update(stack_a, stack_b);
		current_value = 0;
		next_pos = next_number_in_chunk_position(*stack_a, chunker);
		if (next_pos == -1)
		{
			chunker[0] = chunker[1];
			chunker[1] += chunker[2];
			continue ;
		}
		tmp = *stack_a;
		while (tmp->index != next_pos)
			tmp = tmp->next;
		current_value = tmp->value;
		next_pos = find_best_spot(*stack_b, current_value);
		while ((*stack_a)->value != current_value)
		{
			if (*stack_b && tmp->index < (int)(*stack_a)->size / 2 && next_pos < (int)(*stack_b)->size / 2 && next_pos > 0)
				operation[RR](stack_a, stack_b);
			else if (*stack_b && tmp->index > (int)(*stack_a)->size / 2 && next_pos > (int)(*stack_b)->size / 2 && next_pos < (int)(*stack_b)->size)
				operation[RRR](stack_a, stack_b);
			else if (tmp->index < (int)(*stack_a)->size / 2)
				operation[RA](stack_a, NULL);
			else
				operation[RRA](stack_a, NULL);
			(*count)++;
		}
		(*count)++;
		operation[PB](stack_a, stack_b);
		if ((*stack_a)->size == 0)
		{
			operation[PB](stack_a, stack_b);
			break;
		}
	}
	return ;
	while ((*stack_b)->size)
	{
		stacks_update(stack_a, stack_b);
		next_pos = next_number_in_chunk_position(*stack_b, chunker);
		if (next_pos == -1)
		{
			chunker[1] = chunker[0];
			chunker[0] -= chunker[2];
			continue ;
		}
		tmp = *stack_b;
		while (tmp->index != next_pos)
			tmp = tmp->next;
		current_value = tmp->value;
		next_pos = find_best_spot(*stack_a, current_value);
		while ((*stack_b)->value != current_value)
		{
			if (*stack_a && tmp->index < (int)(*stack_b)->size / 2 && next_pos < (int)(*stack_a)->size / 2 && next_pos > 0)
				operation[RR](stack_a, stack_b);
			else if (*stack_a && tmp->index > (int)(*stack_b)->size / 2 && next_pos > (int)(*stack_a)->size / 2 && next_pos < (int)(*stack_a)->size)
				operation[RRR](stack_a, stack_b);
			else if (tmp->index < (int)(*stack_b)->size / 2)
				operation[RB](stack_b, NULL);
			else
				operation[RRB](stack_b, NULL);
			(*count)++;
		}
		(*count)++;
		operation[PA](stack_a, stack_b);
	}
	operation[PA](stack_a, stack_b);
	free(operation);
}

int	main(int argc, char **argv)
{
	list	*stack_a;
	list	*stack_b;
	ssize_t	count;

	if (argc < 2 || !input_valid_check(argv + 1))
		exit(-1);
	stack_a = input_parse((char const **)argv + 1, argc);
	stack_b = NULL;
	count = 1;
	input_normalize(&stack_a);
	problem_solve(&stack_a, &stack_b, &count);
	debug_print(stack_a, stack_b);
	ft_printf("%d\n", count);
	lst_clear_full(&stack_a);
	lst_clear_full(&stack_b);
	return (0);
}
