/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:22:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/14 11:35:12 by vvobis           ###   ########.fr       */
/*   Updated: 2024/05/06 09:11:45 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	int		divider;
	void	(**operation)(t_node **, t_node **);

	stack_a = input_parse((char const **)argv + 1, argc);
	if (!stack_a || lst_check_sort(stack_a, 0) || !redundancy_check(stack_a))
		return (lst_clear_full(&stack_a), 1);
	stack_b = NULL;
	stacks_update(&stack_a, &stack_b);
	operation = operations_initialize();
	if (!operation)
		return (lst_clear_full(&stack_a), -1);
	input_normalize(&stack_a);
	if (stack_a->size <= 5)
		return (handle_smol(&stack_a, &stack_b, operation), \
				free(operation), 0);
	divider = 1;
	if (stack_a->size > 10)
		divider = 5;
	if (stack_a->size > 300)
		divider = 11;
	push_to_b(&stack_a, &stack_b, operation, stack_a->size / divider);
	return (free(operation), 0);
}
