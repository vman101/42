/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:20:21 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/27 19:26:07 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <sys/types.h>

t_file	*input_setup(char ***argv, int argc)
{
	t_file	*file;

	if (argc != 5)
		exit(print_help());
	(*argv)++;
	file = file_create(*(*argv), O_RDONLY, 0);
	(*argv)++;
	return (file);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	t_file	*file;
	int		pipefd[2];
	pid_t	pids[2];

	file = input_setup(&argv, argc);
	pipe(pipefd);
	cmd = command_create((char **)ft_split(*argv++, ' '), env);
	pids[IN] = pipe_in(cmd, pipefd, file->fd);
	cmd = command_create((char **)ft_split(*argv++, ' '), env);
	file = file_create(*argv, O_WRONLY | O_CREAT, 0644);
	if (dup2(pipefd[PIPE_OUT], 0))
	{
		perror("dup2");
		lst_memory(NULL, NULL, CLEAN);
	}
	pids[OUT] = pipe_out(cmd, file->fd);
	ft_close(pipefd[PIPE_OUT], "main_end");
	wait_pids(pids, 2);
	lst_memory(NULL, NULL, END);
}
