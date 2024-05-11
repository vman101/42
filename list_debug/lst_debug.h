/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:28:10 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/05 10:09:09 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_DEBUG_H

# define LST_DEBUG_H

# include <stdarg.h>
# include "printf/ft_printf.h"
# include "libft/libft.h"

typedef struct s_node LIST;

enum	lst_list_manipulations
{
	NONE,
	MAXIMUM,
	MINIMUM,
	INCREASE,
	FRONT,
	BACK,
};

enum	db_enum_lst_print 
{
	EXIT,
	PRINT_NODE,
	PRINT_TO_END,
	PRINT_FULL,
};

typedef int enum_memb ;

/* PRINT DEBUG INFORMATION BY OFFSET */
void	db_lst_menu(void *node, enum_memb action, int print_amount,  int arg_count, ...);
void	db_lst_node_print(void *node, int print_amount, void **args);
void	db_lst_print_to_end(void *node, int print_amount, void **args);
void	db_lst_print_full(void *node, int print_amount, void **args);
void	db_exit_with_message(void *node, int print_amount, int arg_count, void **args);

/* BASIC LIST MANIP */
LIST	*lst_node_new(int value, int index);
size_t	lst_list_size(LIST *lst);
void	lst_node_add_front(LIST **node, LIST *new);
void	lst_node_add_back(LIST **node, LIST *new);
void	lst_node_del(LIST **lst);
void	lst_clear_full(LIST **head);
void	lst_clear_to_end(LIST **head);
void	lst_node_swap(LIST *n1, LIST *n2);
LIST	*lst_node_last(LIST *head);

/* LIST SORTING AND MEMORY MAINP */
int		lst_check_sort(LIST *head, unsigned int offset);
void	lst_list_information_sync(LIST *lst, unsigned int offset);
void	lst_list_sort_by_offset(LIST **input, unsigned int offset);
void	lst_list_memset(LIST **lst, enum_memb option, unsigned int offset, int value);
int		lst_get_extreme_information(LIST *node, enum_memb extreme, unsigned int offset);

#endif
