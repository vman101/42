/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/06 09:11:45 by victor           ###   ########.fr       */
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
	db_lst_menu(stack_a, PRINT_FULL, 1, 2, "Node value", 0);
	ft_printf("\nStack B\n");
	db_lst_menu(stack_b, PRINT_FULL, 1, 2, "Node value", 0); 
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

	if (!stack)
		return (-1);
	max = lst_get_extreme_information(stack, MAXIMUM, 0);
	min = lst_get_extreme_information(stack, MINIMUM, 0);
	if (value < min)
		return (find_rotation(stack, min));
	else if (value > max)
		return (find_rotation(stack, max));
	return (-1);
}

list	*lst_node_extract(list *node, int offset_value, int value)
{
	if (!node)
		return (NULL);
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (*(int *)((char *)node + offset_value) == value)
			return (node);
		 node = node->next;
	}
	return (NULL);
}

void	problem_solve(list **stack_a, list **stack_b, ssize_t *count)
{
	void	(**operation)(list **, list **);
	int		next_index[2];
	list	*candidate[2];

	*count = 0;
	operation = operations_initialize();
	while ((*stack_a)->size >= 3)
		operation[PB](stack_a, stack_b);
	input_sort_three(stack_a, operation);
	candidate[0] = NULL;
	candidate[1] = NULL;
	while ((*stack_a)->next && !candidate[0] && !candidate[1])
	{
		candidate[0] = *stack_a;
		candidate[1] = *stack_a;
		candidate[0] = lst_node_extract(*stack_b, 0, candidate[0]->value + 1);
		candidate[1] = lst_node_extract(*stack_b, 0, candidate[1]->value - 1);
		if ((candidate[0]->index > (*stack_b)->size / 2 && candidate[0]->index > next_index[0]) || candidate[0]->index < (*stack_b)->size / 2 && candidate[0]->index < next_index[0])
			next_index = candidate[0]->index;
		*stack_a = (*stack_a)->next;
	}
	*stack_a = lst_node_extract(*stack_a, 4, 0);
	ft_printf("Candidate high: ");
	db_lst_menu(candidate[0], PRINT_NODE, 2, 4, "Node Value", 0, "Node Index", 4);
	ft_printf("Candidate low: ");
	db_lst_menu(candidate[1], PRINT_NODE, 2, 4, "Node Value", 0, "Node Index", 4);
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
//	debug_print(stack_a, stack_b);
	ft_printf("%d\n", count);
	lst_clear_full(&stack_a);
	lst_clear_full(&stack_b);
	return (0);
}
