/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:17:14 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/15 14:03:52 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_destroy(void *file_del)
{
	if (!file_del)
		return ;
	close(((t_file *)file_del)->fd);
	free(file_del);
}

void	command_destroy(void *cmd_del)
{
	if (!cmd_del)
		return ;
	free((t_cmd *)cmd_del);
}

t_cmd	*command_create(char **input, char **env, t_file *files)
{
	t_cmd	*cmd_new;

	if (!input || !*input)
		return (NULL);
	lst_memory(input, &free_split, ADD);
	cmd_new = ft_calloc(1, sizeof(*cmd_new));
	lst_memory(cmd_new, &command_destroy, ADD);
	cmd_new->argv = input;
	cmd_new->path_absolute = find_absolute_path(env, *input);
	if (!cmd_new->path_absolute)
		return (NULL);
	cmd_new->env = env;
	cmd_new->file = files;
	return (cmd_new);
}

t_file	*file_create(char const *path, int flag, int mode)
{
	t_file	*file_new;

	if (!path)
		return (NULL);
	file_new = malloc(sizeof(*file_new));
	lst_memory(file_new, &file_destroy, ADD);
	file_new->fd = open(path, flag, mode);
	if (file_new->fd == -1 && mode == O_RDONLY)
		return (p_stderr(STDERR_FILENO, \
				"pipex: %s: No such file or directory\n", path), \
				lst_memory(NULL, NULL, CLEAN), NULL);
	else if (file_new->fd == -1)
	{
		p_stderr(STDERR_FILENO, "pipex: %s: ", path);
		perror("");
		lst_memory(NULL, NULL, CLEAN);
	}
	file_new->mode = mode;
	file_new->path = (char *)path;
	return (file_new);
}
