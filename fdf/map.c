/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:02:02 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/23 17:13:50 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "inc/fdf.h"

void	map_destroy(t_map *map)
{
	free(map->p);
	free(map);
}

int	get_split_len(char const **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	get_row_len(char const ***row)
{
	int	i;

	i = 0;
	while (row[i])
		i++;
	return (i);
}

int map_get_rows(char const *path, char ****row)
{
	int	fd;
	int i;
	char *buf;
	char **tmp;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		if (row)
		{
			tmp = ft_split(buf, ' ');
			row[i] = super_split(tmp, get_split_len((char const **)tmp) + 1, ',');
			free_split(tmp);
		}
		free(buf);
		i++;
	}
	close(fd);
	return (i);
}
