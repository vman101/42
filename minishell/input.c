/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:18:42 by vvobis            #+#    #+#             */
/*   Updated: 2024/07/06 18:29:17 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(void *back)
{
	char	**free_back;

	if (!back)
		return ;
	free_back = (char **)back;
	while (*free_back)
	{
		free(*free_back);
		*free_back = NULL;
		free_back++;
	}
	free(back);
	return ;
}

static int	find_longest_path(char *path)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (*path++)
	{
		if (*path == ':')
		{
			if (ret < i)
			{
				ret = i;
				i = 0;
			}
		}
		i++;
	}
	return (ret);
}

static char	*print_error(char *input)
{
	if (input && ft_strchr(input, '/'))
	{
		if (access(input, F_OK) == 0)
		{
			if (access(input, X_OK) == 0)
				return (input);
			else
				p_stderr(STDERR_FILENO, "minishell: %s: permission denied\n", \
						input);
		}
		else
			p_stderr(STDERR_FILENO, "minishell: %s: no such file or directory\n", \
					input);
	}
	else
		p_stderr(STDERR_FILENO, "minishell: %s: command not found\n", input);
	return (NULL);
}

static char	*check_paths(const char *path, char *path_abs, char *input)
{
	while (path)
	{
		ft_strlcpy(path_abs, path, ft_strchr(path, ':') - path + 1);
		ft_strlcat(path_abs, "/", ft_strlen(path_abs) + 2);
		ft_strlcat(path_abs, input, ft_strlen(input) + ft_strlen(path_abs) + 1);
		if (access(path_abs, F_OK) == 0)
		{
			if (access(path_abs, X_OK) == 0)
				return (path_abs);
		}
		path = ft_strchr(path, ':');
		if (path)
			path++;
	}
	return (print_error(input));
}

char	*find_absolute_path(const char **env, char *input)
{
	char	*path;
	char	*path_abs;
	int		i;

	i = 0;
	if (ft_strchr(input, '/'))
		return (print_error(input));
	path = NULL;
	while (!path)
		path = ft_strnstr(env[i++], "PATH=", ft_strlen("PATH="));
	path = ft_strchr(path, '/');
	path_abs = malloc(find_longest_path(path) + ft_strlen(input) + 2);
	lst_memory(path_abs, &free, ADD);
	return (check_paths(path, path_abs, input));
}
