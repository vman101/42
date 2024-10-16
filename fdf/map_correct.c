/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_correct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:45:59 by vvobis            #+#    #+#             */
/*   Updated: 2024/09/21 12:19:14 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

static void	map_find_extremes(t_point3d *min, t_point3d *max, \
								size_t map_size, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map_size)
	{
		if (map->p[i].z > max->z)
			*max = map->p[i];
		if (map->p[i].z < min->z)
			*min = map->p[i];
		i++;
	}
}

static void	map_set_colors(t_point3d min, t_point3d max, \
							size_t map_size, t_map *map)
{
	size_t	i;
	float	ratio;

	max.color = 0xff0000;
	min.color = 0xffffff;
	i = 0;
	if (max.z == min.z)
		max.color = 0xffffff;
	while (i < map_size)
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

void	map_colors_correct(t_map *map)
{
	size_t		i;
	t_point3d	max;
	t_point3d	min;

	if (!map)
		return ;
	i = 0;
	min = (t_point3d){0};
	max = (t_point3d){0};
	map_find_extremes(&min, &max, map->size, map);
	if (map->colorized == false)
		map_set_colors(min, max, map->size, map);
}
