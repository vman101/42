/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:05:11 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/10 18:45:10 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <sys/types.h>
#include <unistd.h>

void	file_desc_init(int fd[2], char *input, char *output)
{
	fd[IN] = open(input, O_RDONLY);
	fd[OUT] = open(output, O_WRONLY);
}

void	free_all(char **back)
{
	char	**free_back;

	if (!back)
		return ;
	free_back = back;
	while (*back)
	{
		free(*back);
		*back = NULL;
		back++;
	}
	free(free_back);
	return ;
}

int	find_longest_path(char *path)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (*path++)
	{
		if (*path == ':')
			if (ret < i)
			{
				ret = i;
				i = 0;
			}
		i++;
	}
	return (ret);
}

char *absolute_path(char **env, char *input)
{
	char	*path;
	char	*path_abs;
	int		i;

	path = NULL;
	i = 0;
	while (!path)
		path = ft_strnstr(env[i++], "PATH=", ft_strlen("PATH="));
	path = ft_strchr(path, '/');
	path_abs = ft_calloc(find_longest_path(path) + ft_strlen(input) + 2, sizeof(*path_abs));
	while (path)
	{
		ft_strlcpy(path_abs, path, ft_strchr(path, ':') - path + 1);
		ft_strlcat(path_abs, "/", ft_strlen(path_abs) + 2);
		ft_strlcat(path_abs, input, ft_strlen(input) + ft_strlen(path_abs) + 1);
		if (access(path_abs, F_OK) == 0)
			if (access(path_abs, X_OK) == 0)
				return (path_abs);
		path = ft_strchr(path, ':') + 1;
	}
	return (NULL);
}

int main(int argc, char **argv, char **env)
{
	char	**input[2];
	char	*cmd0;
	char	*cmd1;
	int		pipefd[2];
	int		fd[2];
	pid_t	cpid[2];

	if (argc != 5)
		exit (-1);
	input[0] = ft_split(argv[CMD1], 32);
	input[1] = ft_split(argv[CMD2], 32);
	cmd0 = absolute_path(env, input[0][0]);
	cmd1 = absolute_path(env, input[1][0]);
	file_desc_init(fd, argv[FILE_IN], argv[FILE_OUT]);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit (EXIT_FAILURE);
	}

	cpid[0] = fork();
	cpid[1] = fork();
	if (cpid[0] == 0)
	{
		close(pipefd[PIPE_OUT]);
		dup2(fd[IN], 0);
		dup2(pipefd[PIPE_IN], 1);
		execve(cmd0, input[0], env);
		exit(EXIT_SUCCESS);
	}
	else if (cpid[1] == 0)
	{
		close(pipefd[PIPE_IN]);
		dup2(pipefd[PIPE_OUT], 0);
		dup2(fd[OUT], 1);
		wait(NULL);
		execve(cmd1, input[1], env);
	}
	else
	{
		free(cmd0);
		free(cmd1);
		free_all(input[0]);
		free_all(input[1]);
	}
	return (0);
}
