/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:17:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/03 16:17:01 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_H

# define SWAP_H

# define LIST t_node

# include "printf/ft_printf.h"
# include "libft/libft.h"
# include "lst_debug.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				index;
	unsigned int	size;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

enum operations
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
void	input_normalize(LIST **input);
LIST	*input_parse(char const **argv, int argc);

/* BASIC LIST MANIP */

/* OPERATIONS */
void	sa(LIST **head, LIST **null);
void	sb(LIST **head, LIST **null);
void	ss(LIST **head_a, LIST **head_b);
void	ra(LIST **head, LIST **null);
void	rb(LIST **head, LIST **null);
void	rr(LIST **head_a, LIST **head_b);
void	pa(LIST **head_a, LIST **head_b);
void	pb(LIST **head_a, LIST **head_b);
void	rra(LIST **head, LIST **null);
void	rrb(LIST **head, LIST **null);
void	rrr(LIST **head_a, LIST **head_b);

#endif
