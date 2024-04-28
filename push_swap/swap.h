/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:17:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/27 19:41:11 by vvobis           ###   ########.fr       */
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
node_t	*input_parse(char const *argv, size_t *input_size);

/* NODE MANIP */
node_t	*lst_node_new(int value, int index);
void	lst_node_add_back(node_t **node, node_t *new);
void	lst_node_del(node_t *lst);
void	lst_clear_full(node_t **head);
void	lst_clear_to_end(node_t **head);

/* DEBUG */

#endif
