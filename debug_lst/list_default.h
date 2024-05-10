/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_default.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:28:10 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 22:36:45 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_DEBUG_H

# define LST_DEBUG_H

# include <stdarg.h>
# include "printf/ft_printf.h"

typedef struct s_node list;

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

/* BASIC list MANIP */
list	*lst_node_new(int value, int index);
size_t	lst_list_size(list *lst);
void	lst_node_add_front(list **node, list *new);
void	lst_node_add_back(list **node, list *new);
void	lst_node_del(list **lst);
void	lst_clear_full(list **head);
void	lst_clear_to_end(list **head);
void	lst_node_swap(list *n1, list *n2);
list	*lst_node_last(list *head);

/* list SORTING AND MEMORY MAINP */
int		lst_check_sort(list *head, unsigned int offset);
void	lst_list_information_sync(list *lst, unsigned int offset);
void	lst_list_sort_by_offset(list **input, unsigned int offset);
void	lst_list_memset(list **lst, enum_memb option, unsigned int offset, int value);
int		lst_get_extreme_information(list *node, enum_memb extreme, unsigned int offset);
list	*lst_node_extract(list *node, int offset_value, int value);

#endif
