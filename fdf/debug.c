/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:08:43 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/25 12:05:00 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

void	point_print(t_point3d *p)
{
	printf("(x: %f y: %f z: %f color: 0x%x)\n", p->x, p->y, p->z, p->color);
}

void	map_print(t_point3d *p, size_t size)	
{
	size_t i;

	i = 0;
	while (i < size)
	{
		point_print(&p[i]);
		i++;
	}
}

