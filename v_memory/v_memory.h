/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_memory.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:39:19 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/15 17:53:05 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_MEMORY_H

# define V_MEMORY_H
# include "libft.h"

typedef struct s_clean
{
	void			*content;
	void			(*clean)(void *del);
	struct s_clean	*next;
}					t_clean;

enum e_alloc
{
	ADD,
	CLEAN,
	END,
	FREE,
};

t_clean	*lst_node_new(void *content, void (*del)(void *));
void	lst_memory(void *mem, void (*del)(void *c), int mode, char const *specifier);
void	lst_node_del(t_clean **lst);
void	lst_node_del_clean(t_clean **lst, void *mem);
void	lst_list_clean(t_clean **head);
int		lst_add_back(t_clean **node, t_clean *node_new);

#endif
