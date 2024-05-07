/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 12:16:55 by victor           ###   ########.fr       */
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

list	*find_best_spot(list *stack, int value)
{
	list	*upper;
	list	*lower;

	if (!stack)
		return (NULL);
	upper = lst_node_extract(stack, 0, value + 1);
	lower = lst_node_extract(stack, 0, value - 1);
	if (upper && lower)
	{
		if (upper->index >= stack->size / 2 && lower->index >= stack->size / 2)
		{
			if (upper->index > lower->index)
				return (upper);
			else
				return (lower);
		}
		else if (upper->index < stack->size / 2 && lower->index < stack->size / 2)
		{
			if (upper->index < lower->index)
				return (upper);
			else
				return (lower);
		}
		else if (upper->index >= stack->size / 2  && lower->index <= stack->size / 2)
		{
			if (stack->size - upper->index < lower->index)
				return (upper);
			else
				return (lower);
		}
		else if (upper->index <= stack->size / 2 && lower->index >= stack->size / 2)
		{
			if (stack->size - lower->index > upper->index)
				return (upper);	
			else
				return (lower);
		}
	}
	if (!upper && lower)
		return (lower);
	else if (!lower && upper)
		return (upper);
	return (NULL);
}

int	compare_value(int size, int value1, int value2)
{
	if (value1 < value2 && value2 <= size / 2 && value1 <= size / 2)
		return (0);
	if (value1 > value2 && value2 >= size / 2 && value1 >= size / 2)
		return (0);
	if (value1 > value2 && value2 <= size / 2 && size - value1 <= value2)
		return (0);
	if (value1 < value2 && value2 >= size / 2 && size - value2 >= value1)
		return (0);
	return (1);
}

#define A 0
#define B 1

list	**find_pair(list *stack_1, list *stack_2, int desc)
{
	list	**lst_pair; list	*tmp;

	lst_pair = malloc(sizeof(*lst_pair) * 2);
	lst_pair[0] = NULL;
	lst_pair[1] = NULL;
	while (stack_1)
	{
		tmp = find_best_spot(stack_2, stack_1->value);
		if (tmp)
		{
			if (!lst_pair[(desc > 0)] || compare_value(stack_2->size, lst_pair[(desc > 0)]->index, tmp->index))
			{
				lst_pair[(desc > 0)] = find_best_spot(stack_1, tmp->value);
				lst_pair[(desc < 1)] = tmp;
			}
		}
		stack_1 = stack_1->next;
	}
	if (lst_pair[A])
		return (lst_pair);
	free(lst_pair);
	return (NULL);
}

void	free_pair(list ***pair)
{
	free(pair[0]);
	pair[0] = NULL;
	free(pair[1]);
	pair[1] = NULL;
	free(pair);
	pair = NULL;
}

void	connect_pair(list **stack_0, list **stack_1, void (***operation)(list **stack1, list **stack2), list **pair)
{
	while ((pair[0]->index || pair[1]->index) && (pair[0]->index != (*stack_0)->size || pair[1]->index != (*stack_1)->size))
	{
		if (pair[0]->index && pair[1]->index && pair[0]->index < (*stack_0)->size && pair[1]->index < (*stack_1)->size)
			operation[0][RRR](stack_0, stack_1);
		else if (pair[0]->index && pair[1]->index && pair[0]->index > (*stack_0)->size && pair[1]->index > (*stack_1)->size) 
			operation[0][RRRR](stack_0, stack_1);
		else if (pair[0]->index && pair[0]->index <= (*stack_0)->size / 2)
			operation[0][R](stack_0, NULL);
		else if (pair[1]->index && pair[1]->index <= (*stack_1)->size / 2)
			operation[1][R](stack_1, NULL);
		else if (pair[0]->index && pair[0]->index > (*stack_0)->size / 2)
			operation[0][RR](stack_0, NULL);
		else if (pair[1]->index && pair[1]->index > (*stack_1)->size / 2)
			operation[1][RR](stack_1, NULL);
		stacks_update(stack_0, stack_1);
	}
	if (pair[A]->value < pair[B]->value)
		operation[B][R](stack_1, NULL);
}

void	problem_solve(list **stack_a, list **stack_b)
{
	void	(***operation)(list **, list **);
	list	***pair;
	int		descriptor[2];

	pair = malloc(sizeof(*pair) * 2);
	operation = operations_initialize();
	while ((*stack_a)->size > 3)
		operation[A][P](stack_a, stack_b);
	input_sort_three(stack_a, operation[A]);
	while (*stack_b)
	{
		pair[A] = find_pair(*stack_a, *stack_b, A);
		pair[B] = find_pair(*stack_b, *stack_a, B);
		descriptor[A] = (pair[A][A]->value < pair[A][B]->value);
		descriptor[B] = (pair[B][A]->value < pair[B][B]->value);
		if (pair[A][A]->index + pair[A][B]->index + descriptor[A] < pair[B][A]->index + pair[B][B]->index + descriptor[B])
		{
			//db_lst_menu(pair[A][A], PRINT_NODE, 2, 4, "Node value", 0, "Node index", 4);
			//db_lst_menu(pair[A][B], PRINT_NODE, 2, 4, "Node value", 0, "Node index", 4);
			connect_pair(stack_a, stack_b, operation, pair[A]);
			operation[A][P](stack_a, stack_b);
		}
		else
		{
			//db_lst_menu(pair[B][A], PRINT_NODE, 2, 4, "Node value", 0, "Node index", 4);
			//db_lst_menu(pair[B][B], PRINT_NODE, 2, 4, "Node value", 0, "Node index", 4);
			connect_pair(stack_a, stack_b, operation, pair[B]);
			operation[B][P](stack_a, stack_b);
		}
	}
	free(operation);
}

int	main(int argc, char **argv)
{
	list	*stack_a;
	list	*stack_b;

	if (argc < 2 || !input_valid_check(argv + 1))
		exit(-1);
	stack_a = input_parse((char const **)argv + 1, argc);
	stack_b = NULL;
	input_normalize(&stack_a);
	problem_solve(&stack_a, &stack_b);
	debug_print(stack_a, stack_b);
	lst_clear_full(&stack_a);
	lst_clear_full(&stack_b);
	return (0);
}
