/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:20:21 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/08 12:33:52 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

static t_file	*pipe_here_doc(char *delimiter)
{
	char	*buf;
	t_file	*file;

	buf = NULL;
	file = file_create("tmp", O_RDWR | O_CREAT, 0644);
	while (1)
	{
		free(buf);
		buf = get_next_line(0);
		if (ft_strncmp(buf, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		write(file->fd, buf, ft_strlen(buf));
	}
	get_next_line(-1);
	ft_close(file->fd, "here_doc");
	file->fd = open("tmp", O_RDONLY);
	free(buf);
	free(delimiter);
	return (file);
}

static t_file	*input_setup(char ***argv, int argc)
{
	t_file	*file;

	if (argc < 5)
		exit(print_help());
	(*argv)++;
	if (ft_strncmp(*(*argv), "here_doc", ft_strlen(*(*argv))) == 0)
	{
		(*argv)++;
		if (argc < 6)
			return (p_stderr(2, \
					"pipex: here_doc: Insufficient arguments! (min = 6)\n", \
					NULL), lst_memory(NULL, NULL, CLEAN), NULL);
		file = pipe_here_doc(ft_strjoin(**argv, "\n"));
	}
	else
		file = file_create(*(*argv), O_RDONLY, 0);
	(*argv)++;
	return (file);
}

static pid_t	pipe_loop(char **argv, char **env)
{
	t_cmd	*cmd;
	int		pipefd[2];

	cmd = command_create((char **)ft_split(*argv, ' '), env);
	ft_pipe(pipefd, "pipe_loop");
	ft_fork(&cmd->cpid, "pipe_loop");
	if (cmd->cpid == 0)
	{
		ft_close(pipefd[PIPE_OUT], "pipe_loop_child");
		ft_dup2(pipefd[PIPE_IN], 1, "pipe_loop_child");
		execve(cmd->path_absolute, cmd->argv, cmd->env);
		perror("execve");
		lst_memory(NULL, NULL, CLEAN);
	}
	else
	{
		ft_close(pipefd[PIPE_IN], "pipe_loop_parent");
		ft_dup2(pipefd[PIPE_OUT], 0, "pipe_loop_parent");
		ft_close(pipefd[PIPE_OUT], "pipe_loop_parent");
	}
	return (cmd->cpid);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	t_file	*file;
	pid_t	pid_final;
	int		pipefd[2];
	int		i;

	i = 0;
	file = input_setup(&argv, argc);
	ft_pipe(pipefd, "in main");
	cmd = command_create((char **)ft_split(*argv++, ' '), env);
	pipe_in(cmd, pipefd, file->fd);
	while (*(argv + 2))
		pipe_loop(argv++, env);
	cmd = command_create((char **)ft_split(*argv++, ' '), env);
	file = file_create(*argv, O_WRONLY | O_CREAT, 0644);
	pid_final = pipe_out(cmd, file->fd);
	lst_memory(NULL, NULL, END);
	return (wait_pids(pid_final, i));
}
