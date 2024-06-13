/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:06:48 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/13 12:49:40 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"
#include <stdbool.h>
#include <unistd.h>

inline t_point3d	point3d_create(float x, float y, float z, t_color color)
{
	return ((t_point3d){x, y, z, color});
}

static int	get_nb(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

static int	map_atoi(char const *s, int b)
{
	int			nb;
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

static void	colors_correct(t_map *map)
{
	size_t		i;
	t_point3d	max;
	t_point3d	min;
	float		ratio;

	i = 0;
	min = (t_point3d){0};
	max = (t_point3d){0};
	while (i < map->width * map->height)
	{
		if (map->p[i].z > max.z)
			max = map->p[i];
		if (map->p[i].z < min.z)
			min = map->p[i];
		i++;
	}
	i = 0;
	if (map->colorized == false)
	{
		max.color = 0xff0000;
		min.color = 0xffffff;
		while (i < map->width * map->height)
		{
			if (map->p[i].z == max.z)
				map->p[i].color = max.color;
			else if (map->p[i].z == min.z)
				map->p[i].color = min.color;
			else
			{
				ratio = map->p[i].z / (max.z + 0.0001f);
				map->p[i].color = line_color(min.color, max.color, ratio);
			}
			i++;
		}
	}
}

static void	map_points_create(char ****points, t_map *map)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = 0;
	map->colorized = false;
	while (points[y])
	{
		x = 0;
		while (points[y][x])
		{
			if (map->colorized == false && points[y][x][1])
				map->colorized = true;
			map->p[i++] = point3d_create(x, y, map_atoi(points[y][x][0], 10), \
						map_atoi(points[y][x][1], 16));
			x++;
		}
		y++;
	}
	i = 0;
	while (points[i])
		free_super_split(points[i++]);
	return (free(points), colors_correct(map));
}

t_map	*map_create(char const *path)
{
	t_map	*map;
	char	****input;
	void	*backup;

	map = ft_calloc(1, sizeof(*map));
	if (!map)
		return (NULL);
	map->height = map_get_rows(path, NULL);
	if (map->height == 0)
		return (free(map), NULL);
	input = ft_calloc(map->height + 1, sizeof(*input));
	if (!input)
		return (free(map), NULL);
	if (!map_get_rows(path, input))
		return (print_usage(), free(map), NULL);
	map->width = get_row_len((char const ****)input);
	map->p = ft_calloc(map->height * map->width, sizeof(*map->p));
	if (!map->p)
	{
		backup = input;
		while (*input)
			free_super_split(*input++);
		return (free(backup), free(map), NULL);
	}
	map_points_create(input, map);
	return (map);
}
