/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 22:38:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"
#include <stdio.h>

void	stacks_update(list **stack_a, list **stack_b)
{
	lst_list_memset(stack_a, NONE, 8, \
					lst_list_size(*stack_a));
	lst_list_memset(stack_a, INCREASE, 4, 0);
	lst_list_memset(stack_b, NONE, 8, \
					lst_list_size(*stack_b));
	lst_list_memset(stack_b, INCREASE, 4, 0);
}

list	*next_node_in_chunk(list *stack, int chunk_range)
{
	int		value_counter;
	list	*upper_pos;
	list	*lower_pos;
	list	*tmp;

	value_counter = 0;
	lower_pos = NULL;
	upper_pos = NULL;
	while (value_counter <= chunk_range)
	{
		tmp = lst_node_extract(stack, 0, value_counter);
		if (tmp)
		{
			if (!upper_pos || tmp->index < upper_pos->index)
				upper_pos = tmp;
			else if (!lower_pos || tmp->index > lower_pos->index)
				lower_pos = tmp;
		}
		value_counter++;
	}
	if (!upper_pos && !lower_pos)
		return (NULL);
	if (!upper_pos && lower_pos)
		return (lower_pos);
	if (upper_pos && !lower_pos)
		return (upper_pos);
	if (upper_pos->index < (int)(stack)->size - lower_pos->index)
		return (upper_pos);
	return (lower_pos);
}

void	push_back(	list **stack_a, list **stack_b, \
					void (**operation)(list **a, list **b))
{
	list	*next_pos;

	stacks_update(stack_a, stack_b);
	while (*stack_b)
	{
		next_pos = lst_node_extract(*stack_b, 0, (*stack_b)->size);
		while ((*stack_b)->value != next_pos->value)
		{
			if (next_pos->index < (int)(*stack_b)->size / 2)
				operation[RB](stack_b, NULL);
			else
				operation[RRB](stack_b, NULL);
		}
		operation[PA](stack_a, stack_b);
	}
}

void	push_to_b(	list **stack_a, list **stack_b, \
					void (**operation)(list **a, list **b), \
					int div)
{
	list	*next_pos;
	int		chunker;

	chunker = div;
	while ((*stack_a))
	{
		next_pos = next_node_in_chunk(*stack_a, chunker);
		if (next_pos == NULL)
		{
			chunker += div;
			continue ;
		}
		while ((*stack_a)->value != next_pos->value)
		{
			if (next_pos->index > (*stack_a)->size / 2)
				operation[RRA](stack_a, NULL);
			else if (next_pos->index <= (*stack_a)->size / 2)
				operation[RA](stack_a, NULL);
		}
		operation[PB](stack_a, stack_b);
	}
	push_back(stack_a, stack_b, operation);
}

int	main(int argc, char **argv)
{
	list	*stack_a;
	list	*stack_b;
	int		divider;
	void	(**operation)(list **, list **);

	if (argc < 2 || !input_valid_check(argv + 1))
		exit(-1);
	stack_a = input_parse((char const **)argv + 1, argc);
	stack_b = NULL;
	operation = operations_initialize();
	divider = 5;
	if (stack_a->size > 300)
		divider = 11;
	input_normalize(&stack_a);
	push_to_b(&stack_a, &stack_b, operation, stack_a->size / divider);
	lst_clear_full(&stack_a);
	lst_clear_full(&stack_b);
	free(operation);
	return (0);
}
