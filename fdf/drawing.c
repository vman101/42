/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:08:54 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/31 19:19:42 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

void	draw_point(t_data *data, t_point3d *point, t_color color)
{
	mlx_pixel_put(data->mlx, data->win, \
			data->screen->offset_x + point->x, \
			data->screen->offset_y + point->y, color);
}

static t_color	line_color(t_color s, t_color e, float ratio)
{
	t_color			c;
	unsigned char	sc;
	unsigned char	ec;
	unsigned char	inter_c;
	int				bit_shift;

	bit_shift = 0;
	c = 0;
	while (bit_shift <= 16)
	{
		sc = (s >> bit_shift) & 0xFF;
		ec = (e >> bit_shift) & 0xFF;
		inter_c = sc - ((sc - ec) * ratio);
		c |= (t_color)(inter_c << bit_shift);
		bit_shift += 8;
	}
	return (c);
}

static void	calculate_line(float *err, t_point3d *begin, \
							t_point3d *move, t_point3d *end)
{
	float	e2;
	float	dy;
	float	dx;

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

void	draw_line(t_data *data, t_point3d *begin, t_point3d *end)
{
	float		err;
	t_point3d	move;
	float		total_dist;
	float		ratio;

	total_dist = hypotf(end->x - begin->x, end->y - begin->y);
	move = *begin;
	err = fabs(end->x - begin->x) - fabs(end->y - begin->y);
	while (fabs(move.x - end->x) > TOLERANCE || \
			fabs(move.y - end->y) > TOLERANCE)
	{
		ratio = hypotf(move.x - begin->x, move.y - begin->y) / total_dist;
		move.color = line_color(begin->color, end->color, ratio);
		if (move.x + data->screen->offset_x > 0 && move.y + \
				data->screen->offset_y > 0 && \
				move.x + data->screen->offset_x < data->screen->width && \
				move.y + data->screen->offset_y < data->screen->height)
			img_put_pixel(data, move.x + data->screen->offset_x, \
					move.y + data->screen->offset_y, move.color);
		calculate_line(&err, begin, &move, end);
	}
}
