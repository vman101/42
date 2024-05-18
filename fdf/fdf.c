/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:21:21 by victor            #+#    #+#             */
/*   Updated: 2024/05/18 17:24:07 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <math.h>

void draw_point(t_data *data, t_point point, t_color color)
{
    mlx_pixel_put(data->mlx, data->win, point.x, point.y, color); // White color
}

void	calculate_line(int *err, t_point begin, t_point *move, t_point *end)
{
	int e2;
	int dy;
	int dx;

	dx = abs(end->x - begin.x);
	dy = abs(end->y - begin.y);
	e2 = *err * 2;
	if (e2 > -dy)
	{
		*err -= dy;
		if (begin.x < end->x)
			move->x++;
		else
			move->x--;
	}
	if (e2 < dx)
	{
		*err += dx;
		if (begin.y < end->y)
			move->y++;
		else
			move->y--;
	}
}

void draw_line(t_data *data, t_point begin, t_point end, t_color color)
{
	int	err;
	t_point move;

	move = begin;
	err = abs(end.x - begin.x) - abs(end.y - begin.y);
	while (move.x != end.x || move.y != end.y)
	{
		calculate_line(&err, begin, &move, &end);
		draw_point(data, move, color);
	}
}

int	key_press(int keycode, t_data *data)
{
	ft_printf("%d\n", keycode);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit (EXIT_SUCCESS);
	}
	return (1);
}

int main(void)
{
    t_data data;
	t_point b = {20, 20};
	t_point e = {500, 500};

    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    data.win = mlx_new_window(data.mlx, 800, 600, "Line");
    if (!data.win)
        return (1);
	draw_line(&data, b, e, 0xffffff);
	mlx_key_hook(data.win, key_press, &data);
    mlx_loop(data.mlx);
    return (0);
}
