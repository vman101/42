/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:17:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 22:40:01 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_H

# define SWAP_H

# define list t_node

# include "printf/ft_printf.h"
# include "list_default.h"
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_node
{
	int				value;
	int				index;
	int				size;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

enum e_operations
{
	RA,
	RB,
	RR,
	SA,
	SB,
	SS,
	RRA,
	RRB,
	RRR,
	PA,
	PB,
};

/* PROBLEM LOGIC */

/* INPUT HANDLING */
int		input_valid_check(char **argv);
char	***super_split(char const **argv, int argc);
void	input_normalize(list **input);
list	*input_parse(char const **argv, int argc);
int		input_sort_three(list **stack_a, void (**op)(list **, list **));

/* LIBFT */
void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_split(char const *s, char const c);
char	*ft_substr(char const *str, unsigned int start, size_t len);
int		ft_atoi(char const *s);
int		ft_isdigit(char c);

/* BASIC list MANIP */
void	stacks_update(list **stack_a, list **stack_b);

/* OPERATIONS */
void	(**operations_initialize(void))(list **a, list **b);
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
