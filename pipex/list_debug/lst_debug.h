/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:28:10 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/11 16:01:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_DEBUG_H

# define LST_DEBUG_H

# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_clean t_clean;

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

/* BASIC t_clean MANIP */
t_clean	*lst_node_new(void *content, void (*del)(void *content));
void	lst_add_front(t_clean **node, t_clean *node_new);
int		lst_add_back(t_clean **node, t_clean *node_new);
void	lst_node_del(t_clean **lst);
void	lst_clear_full(t_clean **head);
void	lst_clear_to_end(t_clean **head);
t_clean	*lst_node_last(t_clean *head);

/* t_clean SORTING AND MEMORY MAINP */
int		lst_check_sort(t_clean *head, unsigned int offset);
void	lst_list_information_sync(t_clean *lst, unsigned int offset);
void	lst_list_sort_by_offset(t_clean **input, unsigned int offset);
void	lst_list_memset(t_clean **lst, enum_memb option, unsigned int offset, int value);
int		lst_get_extreme_information(t_clean *node, enum_memb extreme, unsigned int offset);

#endif
