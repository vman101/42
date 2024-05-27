/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:20:21 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/27 20:13:20 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

t_file	*pipe_here_doc(char *delimiter)
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

t_file	*input_setup(char ***argv, int argc, pid_t **pids)
{
	t_file	*file;

	if (argc < 5)
		exit(print_help());
	(*argv)++;
	if (ft_strncmp(*(*argv), "here_doc", ft_strlen(*(*argv))) == 0)
	{
		(*argv)++;
		file = pipe_here_doc(ft_strjoin(**argv, "\n"));
	}
	else
		file = file_create(*(*argv), O_RDONLY, 0);
	*pids = malloc(sizeof(*pids) * (argc - 3));
	lst_memory(*pids, free, ADD);
	(*argv)++;
	return (file);
}

void	ft_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		lst_memory(NULL, NULL, CLEAN);
	}
}

void	ft_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		lst_memory(NULL, NULL, CLEAN);
	}
}

pid_t	pipe_loop(char **argv, char **env)
{
	t_cmd	*cmd;
	int		pipefd[2];

	cmd = command_create((char **)ft_split(*argv, ' '), env);
	ft_pipe(pipefd);
	ft_fork(&cmd->cpid);
	if (cmd->cpid == 0)
	{
		ft_close(pipefd[PIPE_OUT], "pipe_loop child");
		if (dup2(pipefd[PIPE_IN], 1) == -1)
			return (perror("dup2"), lst_memory(NULL, NULL, CLEAN), -1);
		execve(cmd->path_absolute, cmd->argv, cmd->env);
		perror("execve");
		lst_memory(NULL, NULL, CLEAN);
	}
	else
	{
		ft_close(pipefd[PIPE_IN], "pipe_loop_parent");
		if (dup2(pipefd[PIPE_OUT], 0) == -1)
			return (perror("dup2"), lst_memory(NULL, NULL, CLEAN), -1);
		ft_close(pipefd[PIPE_OUT], "pipe_loop_parent");
	}
	return (cmd->cpid);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	t_file	*file;
	pid_t	*pids;
	int		pipefd[2];
	int		i;

	i = 0;
	pids = NULL;
	file = input_setup(&argv, argc, &pids);
	pipe(pipefd);
	cmd = command_create((char **)ft_split(*argv++, ' '), env);
	pids[i++] = pipe_in(cmd, pipefd, file->fd);
	while (*(argv + 2))
		pids[i++] = pipe_loop(argv++, env);
	cmd = command_create((char **)ft_split(*argv++, ' '), env);
	file = file_create(*argv, O_WRONLY | O_CREAT, 0644);
	pids[i] = pipe_out(cmd, file->fd);
	wait_pids(pids, i);
	lst_memory(NULL, NULL, END);
}
