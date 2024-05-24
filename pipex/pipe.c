/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:36:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/24 11:44:43 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

pid_t	pipe_in(t_cmd *cmd_in, int pipefd[2], int fd)
{
	cmd_in->cpid = fork();
	if (cmd_in->cpid == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd_in->cpid == 0)
	{
		ft_close(pipefd[PIPE_OUT], "pipe_in child: ");
		if (dup2(pipefd[PIPE_IN], 1) == -1 || dup2(fd, 0) == -1)
			return (p_stderr(STDERR_FILENO, "pipex: %s", "pipe_in_child: "), \
					perror("dup2"), 0);
		execve(cmd_in->path_absolute, cmd_in->argv, cmd_in->env);
		p_stderr(STDERR_FILENO, "pipex: pipe_in: ", NULL);
		perror("execve");
		lst_memory(NULL, NULL, CLEAN);
	}
	else
	{
		ft_close(pipefd[PIPE_IN], "pipe_in_parent: ");
		if (dup2(pipefd[PIPE_OUT], 0))
			return (p_stderr(STDERR_FILENO, "pipex: %s", "pipe_in_parent: "), \
					perror("dup2"), 0);
		ft_close(pipefd[PIPE_OUT], "pipe_in_parent");
	}
	return (cmd_in->cpid);
}

pid_t	pipe_out(t_cmd *cmd_out, int fd)
{
	cmd_out->cpid = fork();
	if (cmd_out->cpid == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd_out->cpid == 0)
	{
		if (dup2(fd, 1) == -1)
			return (perror("dup2"), lst_memory(NULL, NULL, CLEAN), -1);
		execve(cmd_out->path_absolute, cmd_out->argv, cmd_out->env);
		perror("execve");
		lst_memory(NULL, NULL, CLEAN);
	}
	return (cmd_out->cpid);
}

int	wait_pids(pid_t *pids, int pid_count)
{
	int		check_wait;
	int		i;

	i = 0;
	while (pid_count)
	{
		if (pids[i] != -1)
		{
			check_wait = waitpid(pids[i], NULL, WNOHANG);
			if (check_wait == -1)
			{
				perror("waitpid");
				lst_memory(NULL, NULL, CLEAN);
			}
			else if (check_wait > 0)
			{
				pids[i] = -1;
				pid_count--;
			}
		}
		if (i == pid_count)
			i = 0;
		i++;
	}
	return (1);
}
