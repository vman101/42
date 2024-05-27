/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:06:48 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/27 17:49:45 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "inc/fdf.h"

t_point3d point3d_create(float x, float y, float z, t_color color)
{
	t_point3d	p;

	p = (t_point3d){x, y, z, color};
	return (p);
}

static int	get_nb(char c,  char *base)
{
	int	i;

	i = 0;
	while (base [i] && base[i] != c)
		i++;
	return (i);
}

int	map_atoi(char const *s, int b)
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
		nb += get_nb(*tmp, base);
		tmp++;
	}
	if (*s == '-')
		nb = -nb;
	return (nb);
}

t_map	*map_create(char const *path)
{
	t_map	*map;
	char	****input;
	void	*backup;

	map = ft_calloc(1, sizeof(*map));
	map->height = map_get_rows(path, NULL);
	input = ft_calloc(map->height + 1, sizeof(*input));
	if (!input)
		return (free(map), NULL);
	if (!map_get_rows(path, input))
		return (print_usage(), free(map), NULL);
	map->width = get_row_len((char const ***)*input);
	map->p = ft_calloc(map->height * map->width, sizeof(*map->p));
	if (!map->p)
	{
		backup = input;
		while (input)
			free_super_split(*input++);
		return(free(backup), free(map), NULL);
	}
	map_points_create(input, map);
	return (map);
}

void	map_points_create(char ****points, t_map *map)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (points[y])
	{
		x = 0;
		while (points[y][x])
		{
			map->p[i++] = point3d_create(x, y, map_atoi(points[y][x][0], 10), map_atoi(points[y][x][1], 16));
			x++;
		}
		y++;
	}
	i = 0;
	while (points[i])
		free_super_split(points[i++]);
	free(points);
}
