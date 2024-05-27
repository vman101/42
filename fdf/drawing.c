/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:08:54 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/27 18:51:47 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

static void draw_point(t_data *data, t_point3d *point, t_color color)
{
    mlx_pixel_put(data->mlx, data->win, point->x, point->y, color);
}

static t_color line_color(t_color s, t_color e, float ratio)
{
	t_color c;
	unsigned char sc;
	unsigned char ec;   
	int bit_shift;
	unsigned char inter_c;
	
	bit_shift = 0;
	c = 0;
	while (bit_shift <= 16)
	{
	    sc = (s >> bit_shift) & 0xFF;
	    ec = (e >> bit_shift) & 0xFF;
	    inter_c  = sc - (unsigned char)((sc - ec) * ratio);
		if (inter_c > 255)
			inter_c = 255;
		else if (inter_c < 0)
			inter_c = 0;
		c |= (t_color)(inter_c << bit_shift);
	    bit_shift += 8;
	}
	return c;
}

static void	calculate_line(float *err, t_point3d *begin, t_point3d *move, t_point3d *end)
{
	float e2;
	float dy;
	float dx;

	dx = fabs(end->x - begin->x);
	dy = fabs(end->y - begin->y);
	e2 = *err * 2;
	if (e2 > -dy)
	{
		*err -= dy;
		if (begin->x < end->x)
			move->x++;
		else
			move->x--;
	}
	if (e2 < dx)
	{
		*err += dx;
		if (begin->y < end->y)
			move->y++;
		else
			move->y--;
	}
}

void draw_line(t_data *data, t_point3d *begin, t_point3d *end)
{
	float	err;
	t_point3d move;
	float	total_dist = hypotf(end->x - begin->x, end->y - begin->y);
	float	ratio;

	move = *begin;
	err = fabs(end->x - begin->x) - fabs(end->y - begin->y);
	while (fabs(move.x - end->x) > TOLERANCE || fabs(move.y - end->y) > TOLERANCE)
	{
		ratio = hypotf(move.x - begin->x, move.y - begin->y) / total_dist;
		move.color = line_color(begin->color, end->color, ratio);
		draw_point(data, &move, move.color);
		calculate_line(&err, begin, &move, end);
	}
}

void	draw_projected(t_data *data)
{
	size_t	i;
	size_t	j;

	mlx_clear_window(data->mlx, data->win);
	map_copy(data->map, data->map_projected);
	map_scale(data->map_projected, data->screen, data->scale / 2.f, data->map->height * data->map->width);
	rotate_z(data->map, data->map_projected, data->screen->angle_z);
	rotate_y(data->map, data->map_projected, data->screen->angle_y);
	rotate_x(data->map, data->map_projected, data->screen->angle_x);
	i = 0;
	while (data->map->height > i)
	{
		j = 0;
		while (data->map->width != j)
		{
			if (j + 1 < data->map->width)
				draw_line(data, &data->map_projected[j + data->map->width * i], &data->map_projected[j + 1 + data->map->width * i]);
			if (i + 1 < data->map->height)
				draw_line(data, &data->map_projected[j + data->map->width * i], &data->map_projected[j + data->map->width * (i + 1)]);
			j++;
		}
		i++;
	}
}
