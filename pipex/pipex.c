/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:20:21 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/14 14:29:52 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_file	*input_setup(char ***argv, int argc)
{
	t_file	*file;

	if (argc != 5)
		exit(print_help());
	if (!argv)
		return (lst_memory(NULL, NULL, CLEAN), \
				p_stderr(2, "pipex: Invalid argv pointer!\n", NULL), NULL);
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
	pid_t	pid_end;

	file = input_setup(&argv, argc);
	ft_pipe(pipefd, "in main");
	cmd = command_create((char **)ft_split(*argv++, ' '), env);
	if (file->fd != -1)
		pipe_in(cmd, pipefd, file->fd);
	cmd = command_create((char **)ft_split(*argv++, ' '), env);
	file = file_create(*argv, O_WRONLY | O_CREAT, 0644);
	ft_dup2(pipefd[PIPE_OUT], 0, "in main");
	pid_end = pipe_out(cmd, file->fd);
	ft_close(pipefd[PIPE_OUT], "main_end");
	lst_memory(NULL, NULL, END);
	return (wait_pids(pid_end, 2));
}
