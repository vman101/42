/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:59:52 by victor            #+#    #+#             */
/*   Updated: 2024/05/09 17:26:20 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

t_node	*next_node_in_chunk(t_node *stack, int chunk_range, bool dir)
{
	int		value_counter;
	t_node	*next_pos;
	t_node	*tmp;

	if (!dir)
		value_counter = 0;
	else
		value_counter = chunk_range;
	next_pos = NULL;
	while (value_counter <= chunk_range && value_counter >= 0)
	{
		tmp = lst_node_extract(stack, 0, value_counter);
		if (tmp)
			if (!next_pos || (tmp->index < next_pos->index && next_pos->index < \
				stack->size / 2) || (tmp->index > next_pos->index && \
				next_pos->index > stack->size / 2))
				next_pos = tmp;
		if (!dir)
			value_counter++;
		else
			value_counter--;
	}
	return (next_pos);
}

void	push_back(	t_node **stack_a, t_node **stack_b, \
					void (**operation)(t_node **a, t_node **b))
{
	t_node	*next_pos;

	stacks_update(stack_a, stack_b);
	while (*stack_b)
	{
		next_pos = lst_node_extract(*stack_b, 0, (*stack_b)->size - 1);
		while ((*stack_b)->value != next_pos->value)
		{
			if (next_pos->index < (int)(*stack_b)->size / 2)
				operation[RB](stack_b, NULL);
			else
				operation[RRB](stack_b, NULL);
		}
		operation[PA](stack_a, stack_b);
	}
	lst_clear_full(stack_a);
	lst_clear_full(stack_b);
}

void	push_to_b(	t_node **stack_a, t_node **stack_b, \
					void (**operation)(t_node **a, t_node **b), \
					int div)
{
	t_node	*next_pos;
	t_node	*b_pos;
	int		chunker;

	chunker = div;
	next_pos = NULL;
	b_pos = NULL;
	while ((*stack_a))
	{
		next_pos = next_node_in_chunk(*stack_a, chunker, \
					(*stack_b && (*stack_b)->value < chunker / 2));
		if (next_pos == NULL)
		{
			chunker += div;
			continue ;
		}
		if (*stack_b)
			b_pos = next_node_in_chunk(*stack_b, next_pos->value, \
					(next_pos->value > (chunker / 2)));
		stack_rotate((t_node *[2]){next_pos, b_pos}, stack_a, stack_b, \
						operation);
		operation[PB](stack_a, stack_b);
	}
	push_back(stack_a, stack_b, operation);
}

int	handle_smol(t_node **stack_a, t_node **stack_b,
				void (**operation)(t_node **a, t_node **b))
{
	t_node	*next_pos;
	int		current_value;

	current_value = 0;
	while ((*stack_a)->size > 3)
	{
		next_pos = lst_node_extract(*stack_a, 0, current_value++);
		stack_rotate((t_node *[2]){next_pos, NULL}, stack_a, stack_b, \
						operation);
		operation[PB](stack_a, stack_b);
	}
	input_sort_three(stack_a, operation);
	while (*stack_b)
		operation[PA](stack_a, stack_b);
	lst_clear_full(stack_a);
	lst_clear_full(stack_b);
	return (1);
}
