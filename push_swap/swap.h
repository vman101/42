/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:17:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 11:21:25 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_H

# define SWAP_H
# define LOW 0
# define HIGH 1


# define list t_node

# include "printf/ft_printf.h"
# include "libft/libft.h"
# include "lst_debug.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				index;
	int	size;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

enum e_operations
{
	R,
	RRR,
	S,
	SS,
	RR,
	RRRR,
	P,
};

/* PROBLEM LOGIC */

/* INPUT HANDLING */
int		input_valid_check(char **argv);
char	***super_split(char const **argv, int argc);
void	input_normalize(list **input);
list	*input_parse(char const **argv, int argc);
int		input_sort_three(list **stack_a, void (**op)(list **, list **));
void	(***operations_initialize(void))(list **a, list **b);

/* BASIC list MANIP */

/* OPERATIONS */
void	sa(list **head, list **null);
void	sb(list **head, list **null);
void	ss(list **head_a, list **head_b);
void	ra(list **head, list **null);
void	rb(list **head, list **null);
void	rr(list **head_a, list **head_b);
void	pa(list **head_a, list **head_b);
void	pb(list **head_a, list **head_b);
void	rra(list **head, list **null);
void	rrb(list **head, list **null);
void	rrr(list **head_a, list **head_b);

#endif
