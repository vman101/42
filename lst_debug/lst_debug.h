/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:28:10 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/30 14:33:35 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_DEBUG_H
#define LST_DEBUG_H

#include <stdarg.h>
#include "printf/ft_printf.h"
#include "libft/libft.h"

#define BYTE 8

#ifndef LIST
#define LIST node_t

#endif

enum db_enum_lst_print 
{
	EXIT,
	PRINT_NODE,
	PRINT_TO_END,
	PRINT_FULL,
};

typedef int enum_mem ;

void	db_lst_menu(void *node, int print_amount, enum_mem action, int arg_count, ...);
void	db_lst_node_print(void *node, int print_amount, void **args);
void	db_lst_print_to_end(void *node, int print_amount, void **args);
void	db_lst_print_full(void *node, int print_amount, void **args);
void	db_exit_with_message(void *node, int print_amount, int arg_count, void **args);

#endif
