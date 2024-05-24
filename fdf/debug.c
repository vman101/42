/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:08:43 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/24 16:09:38 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

void	point_print(t_point3d *p)
{
	printf("(x: %f y: %f z: %f color: 0x%x)\n", p->x, p->y, p->z, p->color);
}

void	map_print(t_map *map)	
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (map->height > i)
	{
		j = 0;
		while (map->width > j)
			point_print(&map->p[j++ + map->width * i]);
		i++;
	}
}

