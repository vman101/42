/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:51:07 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/16 16:44:07 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

bool	pipe_in2(t_cmd *cmd_in, int pipefd[2][2])
{
	cmd_in->cpid = fork();
	if (cmd_in->cpid == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd_in->cpid == 0)
	{
		if (close(pipefd[1][PIPE_OUT]) == -1)
			return (perror("close"), 0);
		if (dup2(pipefd[1][PIPE_IN], pipefd[0][PIPE_OUT]) == -1)
			return (perror("dup2"), 0);
		if (execve(cmd_in->path_absolute, cmd_in->argv, cmd_in->env) == -1)
			return (perror("execve"), 0);
	}
	return (1);
}

bool	pipe_out2(t_cmd *cmd_out, int pipefd[2][2])
{
	cmd_out->cpid = fork();
	if (cmd_out->cpid == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd_out->cpid == 0)
	{
		if (close(pipefd[0][PIPE_IN]) == -1)
			return (perror("close"), 0);
		if (close(pipefd[1][PIPE_OUT]) == -1)
			return (perror("close"), 0);
		if (dup2(pipefd[0][PIPE_OUT], pipefd[1][PIPE_IN]) == -1)
			return (perror("dup2"), 0);
		if (execve(cmd_out->path_absolute, cmd_out->argv, cmd_out->env))
			return (perror("execve"), 0);
	}
	return (1);
}
