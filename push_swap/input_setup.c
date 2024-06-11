/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:37:56 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/11 21:48:40 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

int	input_sort_three(t_node **stack_a, void (**op)(t_node **, t_node **))
{
	int	a;
	int	b;
	int	c;

	if ((*stack_a)->size == 2)
		return (op[SA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	a = *(int *)(*stack_a);
	b = *(int *)((*stack_a)->next);
	c = *(int *)((*stack_a)->next->next);
	if (a > b && b < c && a > c)
		return (op[RA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a > b && b < c && c > a)
		return (op[SA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	if (a > b && b > c)
		return (op[SA](stack_a, NULL), op[RRA](stack_a, NULL), \
				lst_check_sort(*stack_a, 0));
	if (a < b && b > c && c > a)
		return (op[SA](stack_a, NULL), op[RA](stack_a, NULL), \
				lst_check_sort(*stack_a, 0));
	if (a < b && c < a)
		return (op[RRA](stack_a, NULL), lst_check_sort(*stack_a, 0));
	return (1);
}

void	(**operations_initialize(void))(t_node **a, t_node **b)
{
	void	(**tmp)(t_node **a, t_node **b);

	tmp = malloc(sizeof(void (*)(t_node **, t_node **)) * 11);
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

void	input_normalize(t_node **input)
{
	lst_list_sort_by_offset(input, 0);
	lst_list_memset(input, INCREASE, 0, 0);
	lst_list_sort_by_offset(input, 4);
}

int	redundancy_check(t_node *stack_a)
{
	t_node	*tmp;

	while (stack_a->next)
	{
		tmp = stack_a->next;
		while (tmp)
		{
			if (tmp->value == stack_a->value || tmp->value == -1)
			{
				ft_putstr_fd("Error\n", 2);
				return (0);
			}
			tmp = tmp->next;
		}
		stack_a = stack_a->next;
	}
	return (1);
}

int	input_valid_check(char **argv)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (!ft_isdigit(argv[j][i]) && argv[j][i] != 32)
			{
				ft_putstr_fd("Error\n", 2);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}
