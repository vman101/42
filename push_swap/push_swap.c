/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/06 21:48:27 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"
#include <stdio.h>

void	screen_clear()
{
	ft_printf("\033[2J\033[H");
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

void	debug_print(list *stack_a, list *stack_b)
{
	ft_printf("\nStack A\n");
	db_lst_menu(stack_a, PRINT_FULL, 2, 4, "Node value", 0, "Node index", 4);
	ft_printf("\nStack B\n");
	db_lst_menu(stack_b, PRINT_FULL, 2, 4, "Node value", 0, "Node index", 4); 
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

list	*find_best_spot(list *stack, int value, int *desc)
{
	list	*upper;
	list	*lower;

	if (!stack)
		return (NULL);
	upper = lst_node_extract(stack, 0, value + 1);
	lower = lst_node_extract(stack, 0, value - 1);
	if (upper && lower)
	{
		if (upper->index > stack->size / 2 && lower->index > stack->size / 2)
			if (upper->index > lower->index)
				return (*desc = HIGH, upper);
			else
				return (*desc = LOW, lower);
		else if (upper->index < lower->index)
			return (*desc = HIGH, upper);
		return (*desc = LOW, lower);
	}
	if (!upper && lower)
		return (*desc = LOW, lower);
	else if (!lower && upper)
		return (*desc = HIGH, upper);
	return (NULL);
}

int	compare_value(int size, int value1, int value2)
{
	if (value1 < value2 && value2 < size / 2 && value1 < size / 2)
		return (0);
	if (value1 > value2 && value2 > size / 2 && value1 > size / 2)
		return (0);
	return (1);
}

void	problem_solve(list **stack_a, list **stack_b, ssize_t *count)
{
	void	(**operation)(list **, list **);
	int		descriptor[2];
	int		to_move;
	list	*a_move;
	list	*b_move;
	list	*a_index;
	list	*b_index;
	list	*test_index;

	*count = 0;
	operation = operations_initialize();
	while ((*stack_a)->size >= 3)
		operation[PB](stack_a, stack_b);
	input_sort_three(stack_a, operation);
	while (!lst_check_sort(*stack_a, 0))
	{
		a_index = NULL;
		b_index = NULL;
		a_move = *stack_a;
		while (a_move)
		{
			stacks_update(stack_a, stack_b);
			b_move = *stack_b;
			test_index = find_best_spot(*stack_b, a_move->value, &descriptor[0]);
			if (test_index)
			{
				if(!a_index || compare_value((*stack_b)->size, a_index->index, test_index->index))
					a_index = test_index;
			} 
			while (b_move)
			{
				test_index = find_best_spot(*stack_a, b_move->value, &descriptor[1]);
				if (test_index)
				{
					if(!b_index || compare_value((*stack_a)->size, b_index->index, test_index->index))
						b_index = test_index;
				} 
				b_move = b_move->next;
			}
			a_move = a_move->next;
		}
		if (compare)
		test_index = a_index;
		a_index = find_best_spot(*stack_a, a_index->value, &descriptor[0]);
		to_move = test_index->index + (a_index->value < test_index->value);
		while (to_move > 0 && to_move < (*stack_b)->size)
		{
			if (to_move < (*stack_b)->size / 2)
			{
				to_move--;
				operation[RB](stack_b, NULL);
			}
			else
			{
				to_move++;
				operation[RRB](stack_b, NULL);
			}
			stacks_update(stack_a, stack_b);
		}
		operation[PB](stack_a, stack_b);
	}
	debug_print(*stack_a, *stack_b);
	ft_printf("A: %d", descriptor[0]);
	db_lst_menu(a_index, PRINT_NODE, 2, 4, "Node value", 0, "Node index", 4);
	ft_printf("B: %d", descriptor[1]);
	db_lst_menu(b_index, PRINT_NODE, 2, 4, "Node value", 0, "Node index", 4);
	ft_printf("TEST: ");
	db_lst_menu(test_index, PRINT_NODE, 2, 4, "Node value", 0, "Node index", 4);
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
