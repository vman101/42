/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:11:14 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/28 14:42:07 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"
#include "lst_debug.h"

static char	**free_all(char **back, int i)
{
	char	**tmp;

	tmp = back;
	while (i--)
	{
		free(*back);
		back++;
	}
	free(tmp);
	return (NULL);
}

void	db_lst_menu(void *node, enum_mem action, int print_amount, int arg_count, ...)
{
	va_list args;
	void **args_extract;
	void **args_free;
	int i;

	i = 0;
	args_extract = malloc(sizeof(*args_extract) * (arg_count + 1));
	if (!args_extract)
		exit(EXIT_FAILURE);
	args_free = args_extract;
	va_start(args, arg_count);
	while (i < arg_count)
	{
		args_extract[i++] = (void *)ft_strdup(va_arg(args, char *));
		if (i == arg_count)
			break;
		args_extract[i++] = (void *)ft_itoa(va_arg(args, int));
	}
	args_extract[i] = NULL;
	switch (action)
	{
		case EXIT:
			db_exit_with_message(node, print_amount, arg_count, args_extract);
			break ;
		case PRINT_NODE:
			db_lst_node_print(node, print_amount, arg_count, args_extract);
			break ;
		case PRINT_TO_END:
			db_lst_print_to_end(node, print_amount, arg_count, args_extract);
			break ;
		case PRINT_FULL:
			db_lst_print_full(node, print_amount, arg_count, args_extract);
			break;
	}
	free_all((char **)args_free, i + 1);
	va_end(args);
}

void	db_lst_node_print(void *node, int print_amount, int arg_count, void **args)
{
	arg_count = 0;
	ft_printf("\n----------------------------------------------------------\n");
		while (print_amount--)
		{
			ft_printf("%s: ", *(char **)args);
			args++;
			ft_printf("%d", (int)*((char *)node + ft_atoi(*(char **)args)));
			args++;
			ft_printf("\n");
		}
	ft_printf("----------------------------------------------------------\n");
}

void	db_lst_print_to_end(void *node, int print_amount, int arg_count, void **args)
{
	while (node)
	{
		db_lst_node_print(node, print_amount, arg_count, args);
		node = ((LIST *)node)->next;
	}
}

void	db_lst_print_full(void *node, int print_amount, int arg_count, void **args)
{
	while (((LIST *)node)->prev)
		node = ((LIST *)node)->prev;
	db_lst_print_to_end(node, print_amount, arg_count, args);
}

void	db_exit_with_message(void *node, int print_amount, int arg_count, void **args)
{
	ft_printf("Failed at: ");
	db_lst_node_print(node, print_amount, arg_count, args);
	lst_clear_full((LIST **)&node);
	ft_printf("Error Message: %s", (char *)args[arg_count - 1]);
	free_all((char **)args, arg_count + 1);
	exit(EXIT_FAILURE);
}
