/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:08:54 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/24 16:51:27 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

static void draw_point(t_data *data, t_point3d *point, t_color color)
{
	int screen_x;
	int	screen_y;

	screen_x = (point->x + data->screen->offset_x);
	screen_y = (point->y + data->screen->offset_y);
    mlx_pixel_put(data->mlx, data->win, screen_x, screen_y ,color);
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

	move = *begin;
	err = fabs(end->x - begin->x) - fabs(end->y - begin->y);
	float	tolerance = 0.001;
	while (fabs(move.x - end->x) > tolerance || fabs(move.y - end->y) > tolerance)
	{
		if (begin->color == 0xffffff || end->color == 0xffffff)
			draw_point(data, &move, 0xffffff);
		else
			draw_point(data, &move, begin->color);
		calculate_line(&err, begin, &move, end);
	}
	if (begin->color == 0xffffff || end->color == 0xffffff)
		draw_point(data, &move, 0xffffff);
	else
		draw_point(data, &move, begin->color);
}
/**/
/*void	map_draw(t_data *data)*/
/*{*/
/*	size_t	i;*/
/*	size_t	j;*/
/**/
/*	i = 0;*/
/*	while (data->map->height > i)*/
/*	{*/
/*		j = 0;*/
/*		while (data->map->width != j)*/
/*		{*/
/*			if (j + 1 < data->map->width)*/
/*				draw_line(data, &data->map->p[j + data->map->width * i], &data->map->p[j + 1 + data->map->width * i]);*/
/*			if (i + 1 < data->map->height)*/
/*				draw_line(data, &data->map->p[j + data->map->width * i], &data->map->p[j + data->map->width * (i + 1)]);*/
/*			j++;*/
/*		}*/
/*		i++;*/
/*	}*/
/*}*/
