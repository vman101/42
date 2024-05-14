/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:05:11 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/14 20:02:15 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void	lst_memory(void *mem, void (*del)(void *c), int mode)
{
	static t_clean	*list;
	t_clean			*new;

	if (mode == CLEAN)
	{
		lst_list_clean(&list);
		exit(EXIT_FAILURE);
	}
	if (mode == END)
	{
		lst_list_clean(&list);
		exit(EXIT_SUCCESS);
	}
	if (!mem)
	{
		lst_list_clean(&list);
		exit(EXIT_FAILURE);
	}
	new = lst_node_new(mem, del);
	if (!new)
	{
		del(mem);
		lst_list_clean(&list);
		exit(EXIT_FAILURE);
	}
	lst_add_back(&list, new);
}

int main(int argc, char **argv, char **env)
{
	t_cmd	**cmd;
	t_file	*file;
	int		pipefd[2];

	(void)argc;
	cmd = malloc(sizeof(cmd) * 2);
	lst_memory(cmd, &free, ADD);
	file = file_create(argv[FILE_IN], O_RDONLY);
	cmd[IN] = command_create(ft_split(argv[CMD0], ' '), env, file);
	file = file_create(argv[FILE_OUT], O_WRONLY | O_CREAT);
	cmd[OUT] = command_create(ft_split(argv[CMD1], ' '), env, file);
	if (pipe(pipefd) == -1)
		lst_memory(NULL, NULL, CLEAN);
	if (!pipe_in(cmd[IN], pipefd))
		lst_memory(NULL, NULL, CLEAN);
	if (!pipe_out(cmd[OUT], pipefd))
		lst_memory(NULL, NULL, CLEAN);
	if (cmd[OUT]->cpid > 0 && cmd[IN]->cpid > 0)
		waitpid(cmd[IN]->cpid, NULL, 0);
	lst_memory(NULL, NULL, CLEAN);
	return (0);
}
