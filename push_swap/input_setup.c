/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:57:34 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/06 16:59:44 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

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

void	input_normalize(list **input)
{
	lst_list_sort_by_offset(input, 0);
	lst_list_memset(input, INCREASE, 0, 0);
	lst_list_sort_by_offset(input, 4);
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

