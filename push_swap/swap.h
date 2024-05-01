/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:17:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/01 09:38:40 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_H

# define SWAP_H

# include "printf/ft_printf.h"
# include "libft/libft.h"
# include "lst_debug.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_node
{
	int		value;
	int		index;
	struct	s_node	*prev;
	struct	s_node	*next;
}	node_t;

/* INPUT HANDLING */
node_t	*input_parse(char const *argv);

/* NODE MANIP */
node_t	*lst_node_new(int value, int index);
void	lst_node_add_front(node_t **node, node_t *new);
void	lst_node_add_back(node_t **node, node_t *new);
void	lst_node_del(node_t **lst);
void	lst_clear_full(node_t **head);
void	lst_clear_to_end(node_t **head);
void	lst_node_swap(node_t *n1, node_t *n2);
node_t	*lst_node_last(node_t *head);

/* OPERATIONS */
void	s_a_b(node_t **head);
void	ss(node_t **head_a, node_t **head_b);
void	r_a_b(node_t **head);
void	rr(node_t **head_a, node_t **head_b);
void	pa(node_t **head_a, node_t **head_b);
void	pb(node_t **head_a, node_t **head_b);
void	rr_a_b(node_t **head);
void	rrr(node_t **head_a, node_t **head_b);

/* DEBUG */

#endif
