/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:36:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/09 16:53:18 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_in(t_cmd *cmd_in, int pipefd[2], int fd)
{
	ft_fork(&cmd_in->cpid, "pipe_in");
	if (cmd_in->cpid == 0)
	{
		ft_close(pipefd[PIPE_OUT], "pipe_in_child");
		ft_dup2(pipefd[PIPE_IN], 1, "pipe_in_child, PIPE_IN");
		ft_dup2(fd, 0, "pipe_in_child, PIPE_IN");
		execve(cmd_in->path_absolute, cmd_in->argv, cmd_in->env);
		p_stderr(STDERR_FILENO, "pipex: pipe_in: ", NULL);
		perror("execve");
		lst_memory(NULL, NULL, CLEAN);
	}
	else
	{
		ft_close(pipefd[PIPE_IN], "pipe_in_parent");
		ft_dup2(pipefd[PIPE_OUT], 0, "pipe_in_parent");
	}
}

pid_t	pipe_out(t_cmd *cmd_out, int fd)
{
	ft_fork(&cmd_out->cpid, "pipe_out");
	if (cmd_out->cpid == 0)
	{
		ft_dup2(fd, 1, "pipe_out_child");
		execve(cmd_out->path_absolute, cmd_out->argv, cmd_out->env);
		perror("execve");
		lst_memory(NULL, NULL, CLEAN);
	}
	return (cmd_out->cpid);
}

int	wait_pids(pid_t pids_final, int pid_count)
{
	int		i;
	int		status;
	int		status_test;
	pid_t	wait_pid_ret;

	i = 0;
	status = -1;
	status_test = -1;
	while (i < pid_count)
	{
		wait_pid_ret = wait(&status_test);
		if (wait_pid_ret == -1)
			return (p_stderr(2, "pipex: %s: ", "wait_pids"), perror("wait"), \
					lst_memory(NULL, NULL, CLEAN), 0);
		if (wait_pid_ret == pids_final)
			status = status_test;
		i++;
	}
	return (WEXITSTATUS(status));
}
