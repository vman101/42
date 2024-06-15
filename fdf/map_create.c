/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:06:48 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/15 16:43:24 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

int	check_number(long *nb, int b, char *base, char c)
{
	int	i;

	if (!ft_strchr(base, c))
		return (0);
	i = 0;
	while (base[i] && base[i] != c)
		i++;
	*nb *= b;
	*nb += i;
	return (1);
}

static int	map_atoi(char const *s, int b, bool *flag)
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
		if (!check_number(&nb, b, base, ft_tolower(*tmp++)))
			*flag = true;
	if (*s == '-')
		nb = -nb;
	if (nb == 125)
		printf("%ld\n", nb);
	return (nb);
}

static void	map_points_create(char ****points, t_map *map, bool *flag)
{
	int		x;
	int		y;
	int		i;
	int		row_len;

	i = 0;
	y = -1;
	while (points[++y] && map && *flag == false)
	{
		x = -1;
		row_len = get_row_len((char const ****)&points[y], SINGLE);
		while (++x < row_len)
		{
			if (map->colorized == false && points[y][x][1])
				map->colorized = true;
			map->p[i++] = (t_point3d){x, y, \
					map_atoi(points[y][x][0], 10, flag), \
					map_atoi(points[y][x][1], 16, flag)};
		}
	}
	i = 0;
	while (points[i])
		free_super_split(points[i++]);
	return (ft_free((void **)&points), map_colors_correct(map));
}

static void	*map_size_set(t_map *map, char ****input, bool *flag)
{
	map->width = get_row_len((char const ****)input, MAX);
	if (*flag || map->width == 0)
		return (print_usage(), map_points_create(input, NULL, flag), \
				ft_free((void **)&map), NULL);
	map->size = map->width * map->height;
	map->p = ft_calloc(map->size + 1, sizeof(*map->p));
	if (!map->p)
		return (map_points_create(input, NULL, flag), \
				ft_free((void **)&map), NULL);
	map_points_create(input, map, flag);
	if (*flag)
		return (print_usage(), ft_free((void **)&map->p), \
				ft_free((void **)&map), NULL);
	return (map);
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
	return (map_size_set(map, input, &flag));
}
