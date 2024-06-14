/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:02:02 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/14 18:38:45 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"
#include "libft/libft.h"

int	get_split_len(char const **split)
{
	int	i;

	if (!split)
		return (-1);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	get_row_len(char const ****row, int mode)
{
	int	i;
	int	j;
	int	size;

	if (!row)
		return (0);
	j = 0;
	size = 0;
	while (row[j])
	{
		i = 0;
		while (row[j][i])
			i++;
		if (mode == SINGLE)
			return (i);
		if (j == 0)
			size = i;
		if (i != size)
			return (0);
		j++;
	}
	return (size);
}

static int	line_get(char ****row, char const *buf)
{
	char	**tmp;
	char	*trim;

	trim = ft_strrchr(buf, '\n');
	if (trim)
		*trim = 0;
	tmp = ft_split(buf, ' ');
	*row = super_split(tmp, get_split_len((char const **)tmp) + 1, ',');
	free_split(tmp);
	if (*row == NULL)
		return (0);
	return (1);
}

int	map_get_rows(char const *path, char ****row, bool *flag)
{
	int		fd;
	int		i;
	char	*buf;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), *flag = true, 0);
	while (1)
	{
		buf = get_next_line(fd);
		if (buf == (char *)-1)
			return (*flag = true, 0);
		if (!buf)
			break ;
		if (row)
			if (!line_get(&row[i], buf))
				return (ft_free((void **)&buf), get_next_line(-1), \
						*flag = true, 0);
		ft_free((void **)&buf);
		i++;
	}
	if (close(fd) == -1)
		return (*flag = true, 0);
	return (get_next_line(-1), i);
}
