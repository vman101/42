/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:36:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/11 20:36:40 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	pipe_in(t_cmd *cmd_in, int pipefd[2])
{
	cmd_in->cpid = fork();
	if (cmd_in->cpid == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd_in->cpid == 0)
	{
		close(pipefd[PIPE_OUT]);
		if (dup2(pipefd[PIPE_IN], 1) == -1 || dup2(cmd_in->file->fd, 0) == -1)
		{
			perror("dup2");
			return (0);
		}
		if (execve(cmd_in->path_absolute, cmd_in->argv, cmd_in->env))
		{
			perror("execve");
			return (0);
		}
	}
	return (1);
}

bool	pipe_out(t_cmd *cmd_out, int pipefd[2])
{
	cmd_out->cpid = fork();
	if (cmd_out->cpid == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd_out->cpid == 0)
	{
		close(pipefd[PIPE_IN]);
		if (dup2(pipefd[PIPE_OUT], 0) == -1 || (dup2(cmd_out->file->fd, 1) == -1))
		{
			perror("dup2");
			return (0);
		}
		if (execve(cmd_out->path_absolute, cmd_out->argv, cmd_out->env))
		{
			perror("execve");
			return (0);
		}
	}
	return (1);
}

