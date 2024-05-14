/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:18:42 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/14 20:14:58 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "printf/ft_printf.h"
#include <stdbool.h>

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

int	find_longest_path(char *path)
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

char	*find_absolute_path(char **env, char *input)
{
	char	*path;
	char	*path_abs;
	int		i;

	path = NULL;
	i = 0;
	while (!path)
		path = ft_strnstr(env[i++], "PATH=", ft_strlen("PATH="));
	path = ft_strchr(path, '/');
	path_abs = malloc(find_longest_path(path) + ft_strlen(input) + 2);
	lst_memory(path_abs, &free, ADD);
	while (path)
	{
		ft_strlcpy(path_abs, path, ft_strchr(path, ':') - path + 1);
		ft_strlcat(path_abs, "/", ft_strlen(path_abs) + 2);
		ft_strlcat(path_abs, input, ft_strlen(input) + ft_strlen(path_abs) + 1);
		if (access(path_abs, F_OK) == 0)
			if (access(path_abs, X_OK) == 0)
				return (path_abs);
		path = ft_strchr(path, ':');
		if (path)
			path++;
	}
	if (ft_strchr(input, '/'))
		ft_printf("pipex: no such file or directory: %s\n", input);
	else
		ft_printf("pipex: command not found: %s\n", input);
	return (lst_memory(NULL, NULL, CLEAN), NULL);
}
