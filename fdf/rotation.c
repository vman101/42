/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:54:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/24 18:54:59 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

void rotate_y(t_map *map, t_point3d *p, float theta)
{
	size_t	i;
	float	new_x;
	float	new_z;
	float	sin_theta;
	float	cos_theta;

	sin_theta = sinf(theta);
	cos_theta = cosf(theta);
	i = 0;
	while (i < map->height * map->width)
	{
		new_x = roundf(p[i].x * cos_theta + p[i].z * sin_theta);
		new_z = roundf(p[i].x * sin_theta - p[i].z * cos_theta);
		p[i].x = new_x;
		p[i].z = new_z;
		i++;
	}
}

void rotate_z(t_map *map, t_point3d *p, float theta)
{
	size_t	i;
	float	new_x;
	float	new_y;
	float	sin_theta;
	float	cos_theta;

	sin_theta = sinf(theta);
	cos_theta = cosf(theta);
	i = 0;
	while (i < map->height * map->width)
	{
		new_x = roundf(p[i].x * cos_theta - p[i].y * sin_theta);
		new_y = roundf(p[i].x * sin_theta + p[i].y * cos_theta);
		p[i].x = new_x;
		p[i].y = new_y;
		i++;
	}
}

void	rotate_x(t_map *map, t_point3d *p, float theta)
{
	size_t	i;
	float	new_y;
	float	new_z;
	float	sin_theta;
	float	cos_theta;

	sin_theta = sinf(theta);
	cos_theta = cosf(theta);
	i = 0;
	while (i < map->height * map->width)
	{
		new_y = roundf(p[i].y * cos_theta + p[i].z * sin_theta);
		new_z = roundf(p[i].y * sin_theta - p[i].z * cos_theta);
		p[i].x = new_y;
		p[i].y = new_z;
		i++;
	}
}

