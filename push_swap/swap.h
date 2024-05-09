/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:17:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/09 17:29:41 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_H

# define SWAP_H

# include "printf/ft_printf.h"
# include "libft/libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef int		t_enum_memb;
typedef struct s_node
{
	int				value;
	int				index;
	int				size;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

enum e_list
{
	NONE,
	INCREASE,
};

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

/* INPUT HANDLING */
int		input_valid_check(char **argv);
char	***super_split(char const **argv, int argc);
void	input_normalize(t_node **input);
t_node	*input_parse(char const **argv, int argc);
int		input_sort_three(t_node **stack_a, void (**op)(t_node **, t_node **));
int		redundancy_check(t_node *stack_a);

/* SORT */
int		handle_smol(t_node **stack_a, t_node **stack_b, \
					void (**operation)(t_node **a, t_node **b));
void	push_to_b(t_node **stack_a, t_node **stack_b, \
					void (**operation)(t_node **a, t_node **b), int div);
void	push_to_b(t_node **stack_a, t_node **stack_b, \
					void (**operation)(t_node **a, t_node **b), int div);
void	stack_rotate(t_node *a[2], t_node **s_a, t_node **s_b, \
					void (**op)(t_node **a, t_node **b));
void	push_back(t_node **stack_a, t_node **stack_b, \
					void (**operation)(t_node **a, t_node **b));
t_node	*next_node_in_chunk(t_node *stack, int chunk_range, bool dir);

/* BASIC t_node MANIP */
t_node	*lst_node_new(long value, int index);
size_t	lst_list_size(t_node *lst);
void	lst_node_add_front(t_node **node, t_node *node_new);
int		lst_add_back(t_node **node, t_node *node_new);
void	lst_node_del(t_node **lst);
void	lst_clear_full(t_node **head);
void	lst_clear_to_end(t_node **head);
void	lst_node_swap(t_node *n1, t_node *n2);
t_node	*lst_node_first(t_node *head);
t_node	*lst_node_last(t_node *head);
void	stacks_update(t_node **stack_a, t_node **stack_b);

/* t_node SORTING AND MEMORY MAINP */
int		lst_check_sort(t_node *head, unsigned int offset);
void	lst_list_information_sync(t_node *lst, unsigned int offset);
void	lst_list_sort_by_offset(t_node **input, unsigned int offset);
void	lst_list_memset(t_node **lst, t_enum_memb option, unsigned int offset, \
						int value);
int		lst_get_extreme_information(t_node *node, t_enum_memb extreme, \
									unsigned int offset);
t_node	*lst_node_extract(t_node *node, int offset_value, int value);

/* OPERATIONS */
void	(**operations_initialize(void))(t_node **a, t_node **b);
void	sa(t_node **head, t_node **null);
void	sb(t_node **head, t_node **null);
void	ss(t_node **head_a, t_node **head_b);
void	ra(t_node **head, t_node **null);
void	rb(t_node **head, t_node **null);
void	rr(t_node **head_a, t_node **head_b);
void	pa(t_node **head_a, t_node **head_b);
void	pb(t_node **head_a, t_node **head_b);
void	rra(t_node **head, t_node **null);
void	rrb(t_node **head, t_node **null);
void	rrr(t_node **head_a, t_node **head_b);

#endif
