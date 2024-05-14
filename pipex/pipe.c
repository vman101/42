/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:36:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/14 20:04:56 by vvobis           ###   ########.fr       */
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
		if (close(pipefd[PIPE_OUT]) == -1)
			return (perror("close"), 0);
		if (dup2(pipefd[PIPE_IN], 1) == -1 || dup2(cmd_in->file->fd, 0) == -1)
			return (perror("dup2"), 0);
		if (execve(cmd_in->path_absolute, cmd_in->argv, cmd_in->env) == -1)
			return (perror("execve"), 0);
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
		if (close(pipefd[PIPE_IN]) == -1)
			return (perror("close"), 0);
		if (dup2(pipefd[PIPE_OUT], 0) == -1 || (dup2(cmd_out->file->fd, 1) == -1))
			return (perror("dup2"), 0);
		if (execve(cmd_out->path_absolute, cmd_out->argv, cmd_out->env))
			return (perror("execve"), 0);
	}
	return (1);
}
