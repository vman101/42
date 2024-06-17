/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_memory.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:38:13 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/15 17:53:07 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_memory.h"

void	lst_memory(void *mem, void (*del)(void *c), int mode, char const *specifier)
{
	static t_clean	*list;
	t_clean			*new;

	if (mode == CLEAN)
		return (lst_list_clean(&list), exit(EXIT_FAILURE));
	if (mode == END)
		return (lst_list_clean(&list));
	if (mode == FREE)
		return (lst_node_del_clean(&list, mem));
	if (!mem)
		return (lst_list_clean(&list), ft_printf("Malloc failed at: %s\n", specifier), \
				exit(EXIT_FAILURE));
	new = lst_node_new(mem, del);
	if (!new)
		return (del(mem), lst_list_clean(&list), ft_printf("Malloc failed in lst_memory for: %s\n", specifier), \
				exit(EXIT_FAILURE));
	lst_add_back(&list, new);
}
