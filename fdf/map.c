/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:02:02 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/11 23:41:18 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

int	get_split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	get_row_len(char const ****row)
{
	int	i;
	int	j;
	int	size;

	j = 0;
	size = 0;
	while (row[j])
	{
		i = 0;
		while (row[j][i])
			i++;
		if (i > size)
			size = i;
		j++;
	}
	return (size);
}

void	destroy_points(char ****points, int i)
{
	while (i >= 0)
		free_super_split(points[i--]);
	free(points);
}

void	line_get(char ****row, char *buf)
{
	char	**tmp;

	tmp = ft_split(buf, ' ');
	*row = super_split(tmp, get_split_len(tmp) + 1, ',');
	free_split(tmp);
}

int	map_get_rows(char const *path, char ****row)
{
	int		fd;
	int		i;
	char	*buf;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), 0);
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		if (row)
		{
			line_get(&row[i], buf);
			if (!row[i])
				return (free(buf), get_next_line(-1), \
						destroy_points(row, i), 0);
		}
		free(buf);
		i++;
	}
	close(fd);
	return (i);
}
