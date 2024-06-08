/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:07:59 by victor            #+#    #+#             */
/*   Updated: 2024/06/08 12:08:26 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_close(int fd, const char *specifier)
{
	if (fd == -1)
		return (0);
	if (close(fd) == -1)
	{
		p_stderr(2, "pipex: %s: ", specifier);
		perror("close");
		lst_memory(NULL, NULL, CLEAN);
	}
	return (1);
}

void	ft_pipe(int pipefd[2], const char *specifier)
{
	if (pipe(pipefd) == -1)
	{
		p_stderr(2, "pipex: %s: ", specifier);
		perror("pipe");
		lst_memory(NULL, NULL, CLEAN);
	}
}

void	ft_dup2(int fd_old, int fd_new, const char *specifier)
{
	if (dup2(fd_old, fd_new) == -1)
	{
		p_stderr(2, "pipex: %s: ", specifier);
		perror("dup2");
		lst_memory(NULL, NULL, CLEAN);
	}
}

void	ft_fork(pid_t *pid, const char *specifier)
{
	if (!pid)
	{
		p_stderr(2, "Invalid pointer ft_fork: %s", specifier);
		lst_memory(NULL, NULL, CLEAN);
	}
	else
	{
		*pid = fork();
		if (*pid == -1)
		{
			p_stderr(2, "pipex: %s: ", specifier);
			perror("fork");
			lst_memory(NULL, NULL, CLEAN);
		}
	}
}
