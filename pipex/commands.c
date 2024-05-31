/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:17:14 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/31 14:19:40 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_destroy(void *file_del)
{
	if (!file_del)
		return ;
	if (((t_file *)file_del)->tmp == true)
		unlink(((t_file *)file_del)->path);
	if (((t_file *)file_del)->fd > 0)
		ft_close(((t_file *)file_del)->fd, "file_destroy");
	free(file_del);
}

void	command_destroy(void *cmd_del)
{
	if (!cmd_del)
		return ;
	free((t_cmd *)cmd_del);
}

t_cmd	*command_create(char **input, char **env)
{
	t_cmd	*cmd_new;

	if (!input || !*input)
		return (lst_memory(NULL, NULL, CLEAN), NULL);
	lst_memory(input, &free_split, ADD);
	cmd_new = ft_calloc(1, sizeof(*cmd_new));
	lst_memory(cmd_new, &command_destroy, ADD);
	cmd_new->argv = input;
	cmd_new->path_absolute = find_absolute_path(env, *input);
	if (!cmd_new->path_absolute)
		return (lst_memory(NULL, NULL, CLEAN), NULL);
	cmd_new->env = env;
	return (cmd_new);
}

t_file	*file_create(char const *path, int flag, int mode)
{
	t_file	*file_new;

	if (!path)
		return (NULL);
	file_new = ft_calloc(1, sizeof(*file_new));
	lst_memory(file_new, &file_destroy, ADD);
	if (ft_strncmp(path, "tmp", ft_strlen(path)) == 0)
		file_new->tmp = true;
	else
		file_new->tmp = false;
	file_new->fd = open(path, flag, mode);
	if (file_new->fd == -1)
	{
		if (mode == O_RDONLY)
			return (p_stderr(STDERR_FILENO, \
						"pipex: %s: no such file or directory\n", path), \
					lst_memory(NULL, NULL, CLEAN), NULL);
		else
			return (p_stderr(STDERR_FILENO, "pipex: %s: ", path), \
					perror(""), lst_memory(NULL, NULL, CLEAN), NULL);
	}
	file_new->mode = mode;
	file_new->path = (char *)path;
	return (file_new);
}

int	print_help(void)
{
	ft_printf("Invalid arguments!\n");
	ft_printf("\nUsage: ./pipex file_in cmd1 cmd2 file_out\n");
	return (-1);
}
