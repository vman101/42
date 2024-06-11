/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:35:57 by victor            #+#    #+#             */
/*   Updated: 2024/06/11 23:31:15 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

t_point3d	map_calc_center(t_point3d *p, size_t size)
{
	float		min;
	float		max;
	t_point3d	center;
	size_t		i;
	size_t		j;

	j = 0;
	while (j < 3)
	{
		i = 0;
		min = *((float *)p + j);
		max = *((float *)p + j);
		while (i < size)
		{
			if (*((float *)&p[i] + j) < min)
				min = *((float *)&p[i] + j);
			if (*((float *)&p[i] + j) > max)
				max = *((float *)&p[i] + j);
			i++;
		}
		*((float *)&center + j) = max - min;
		j++;
	}
	return (center);
}

void	substract_center(t_point3d *center, t_point3d *p, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		p[i].x -= center->x / 2;
		p[i].y -= center->y / 2;
		i++;
	}
}

void	map_copy(t_map *map, t_point3d *p)
{
	size_t	i;

	i = 0;
	while (i < map->width * map->height)
	{
		p[i] = map->p[i];
		i++;
	}
}

void	map_scale(t_point3d *p, t_data *data, size_t size)
{
	size_t		i;
	t_point3d	center;

	i = 0;
	while (i < size)
	{
		p[i].x *= data->scale_x;
		p[i].y *= data->scale_x;
		i++;
	}
	center = map_calc_center(p, size);
	substract_center(&center, p, size);
}
