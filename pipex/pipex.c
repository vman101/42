/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:05:11 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/11 20:54:38 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <sys/types.h>
#include <unistd.h>

void	file_destroy(void *file_del)
{
	if (!file_del)
		return ;
	close(((t_file *)file_del)->fd);
	((t_file *)file_del)->path = NULL;
	free(file_del);
}

void	command_destroy(void *cmd_del)
{
	if (!cmd_del)
		return ;
	file_destroy(((t_cmd *)cmd_del)->file);
	free_split(((t_cmd *)cmd_del)->argv);
	free(((t_cmd *)cmd_del)->path_absolute);
	((t_cmd *)cmd_del)->path_absolute = NULL;
	free((t_cmd *)cmd_del);
}

t_cmd	*command_create(char **input, char **env, t_file *files)
{
	t_cmd	*cmd_new;

	if (!input)
		return (file_destroy(files), files = NULL, NULL);
	cmd_new = ft_calloc(1, sizeof(*cmd_new));
	if(!cmd_new)
		return (free_split(input), file_destroy(files), files = NULL, NULL);
	cmd_new->argv = input;
	cmd_new->path_absolute = find_absolute_path(env, *(char **)input);
	if (!cmd_new->path_absolute)
		return (file_destroy(files), files = NULL, command_destroy(cmd_new), cmd_new = NULL, NULL);
	cmd_new->env = env;
	if (files)
		cmd_new->file = files;
	return (cmd_new);
}

void	free_split(char **back)
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

char *find_absolute_path(char **env, char *input)
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
	if (!path_abs)
		return (NULL);
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
	return (free(path_abs), path_abs = NULL, NULL);
}

t_file	*file_create(char const *path, int mode)
{
	t_file	*file_new;

	if (!path)
		return (NULL);
	file_new = malloc(sizeof(*file_new));
	if (!file_new)
		return (NULL);
	file_new->fd = open(path, mode);
	file_new->mode = mode;
	file_new->path = (char *)path;
	return (file_new);
}

int main(int argc, char **argv, char **env)
{
	t_clean	*head;
	t_cmd	**cmd;
	int		pipefd[2];

	(void)argc;
	head = NULL;
	cmd = malloc(sizeof(t_cmd *) * 2);
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	if (!lst_add_back(&head, lst_node_new(cmd, &free)))
	{
		free(cmd);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd[IN] = command_create(ft_split(argv[CMD0], ' '), env, file_create(argv[FILE_IN], O_RDONLY));
	if (!cmd[IN])
	{
		lst_list_clean(&head);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (!lst_add_back(&head, lst_node_new(cmd[IN], &command_destroy)))
	{
		lst_list_clean(&head);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd[OUT] = command_create(ft_split(argv[CMD1], ' '), env, file_create(argv[FILE_OUT], O_WRONLY));
	if (!cmd[OUT])
	{
		lst_list_clean(&head);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (!lst_add_back(&head, lst_node_new(cmd[OUT], &command_destroy)))
	{
		lst_list_clean(&head);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	pipe(pipefd);
	/*if (!pipe_in(cmd[IN], pipefd))*/
	/*{*/
	/*	lst_list_clean(&head);*/
	/*	exit(EXIT_FAILURE);*/
	/*}*/
	/*if (!pipe_out(cmd[OUT], pipefd))*/
	/*{*/
	/*	lst_list_clean(&head);*/
	/*	exit(EXIT_FAILURE);*/
	/*}*/
	wait(NULL);
	lst_list_clean(&head);
	return (0);
}
