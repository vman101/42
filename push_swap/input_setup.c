/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:57:34 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 10:23:27 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	(***operations_initialize(void))(list **a, list **b)
{
	void (***tmp)(list **a, list **b);

	tmp = malloc(sizeof(void (**)(list **, list **)) * 2);
	tmp[0] = malloc(sizeof(void (*)(list **, list **)) * 7);
	tmp[1] = malloc(sizeof(void (*)(list **, list **)) * 7);
	if (!tmp)
		return (NULL);
    tmp[0][0] = ra;
    tmp[0][1] = rr;
    tmp[0][2] = sa;
    tmp[0][3] = ss;
    tmp[0][4] = rra;
    tmp[0][5] = rrr;
    tmp[0][6] = pb;
    tmp[1][0] = rb;
    tmp[1][1] = rr;
    tmp[1][2] = sb;
    tmp[1][3] = ss;
    tmp[1][4] = rrb;
    tmp[1][5] = rrr;
    tmp[1][6] = pa;
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
		return (op[R](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a > b && b < c && c > a)
		return (op[S](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a > b && b > c)
		return (op[S](stack_a, NULL), op[RR](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a < b && b > c && c > a)
		return (op[S](stack_a, NULL), op[R](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a < b && c < a)
		return (op[RR](stack_a, NULL), lst_check_sort(*stack_a, 0));
	return (1);
}

