/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:06:48 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/14 18:52:53 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <unistd.h>

static int	get_nb(char c, char *base)
{
	int	i;

	i = 0;
	if (!ft_strchr(base, c))
		return (-1);
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

void	check_number(long *nb, int b, char *base, char c)
{
	int	new_number;

	new_number = get_nb(c, base);
}

static int	map_atoi(char const *s, int b)
{
	long		nb;
	char const	*tmp;
	char		*base;

	if (!s)
		return (0xffffff);
	if (b == 10)
		base = "0123456789";
	else if (b == 16)
	{
		base = "0123456789abcdef";
		s += 2;
	}
	nb = 0;
	tmp = s;
	if (*tmp == '+' || *tmp == '-')
		tmp++;
	while (*tmp && *tmp != '\n')
	{
		nb *= b;
		nb += get_nb(ft_tolower(*tmp++), base);
	}
	if (*s == '-')
		nb = -nb;
	return (nb);
}

static void	map_points_create(char ****points, t_map *map)
{
	int		x;
	int		y;
	int		i;
	int		row_len;

	i = 0;
	y = -1;
	while (points[++y] && map)
	{
		x = -1;
		row_len = get_row_len((char const ****)&points[y], SINGLE);
		while (++x < row_len)
		{
			if (map->colorized == false && points[y][x][1])
				map->colorized = true;
			map->p[i++] = (t_point3d){x, y, \
					map_atoi(points[y][x][0], 10), \
					map_atoi(points[y][x][1], 16)};
		}
	}
	i = 0;
	while (points[i])
		free_super_split(points[i++]);
	return (ft_free((void **)&points), map_colors_correct(map));
}

t_map	*map_create(char const *path)
{
	t_map	*map;
	char	****input;
	bool	flag;

	map = ft_calloc(1, sizeof(*map));
	if (!map)
		return (NULL);
	flag = false;
	map->height = map_get_rows(path, NULL, &flag);
	input = ft_calloc(map->height + 1, sizeof(*input));
	if (!input || flag)
		return (ft_free((void **)&input), ft_free((void **)&map), NULL);
	map_get_rows(path, input, &flag);
	map->width = get_row_len((char const ****)input, MAX);
	if (flag || map->width == 0)
		return (print_usage(), map_points_create(input, NULL), \
				ft_free((void **)&map), NULL);
	map->size = map->width * map->height;
	map->p = ft_calloc(map->size + 1, sizeof(*map->p));
	if (!map->p)
		return (map_points_create(input, NULL), ft_free((void **)&map), NULL);
	map_points_create(input, map);
	return (map);
}
