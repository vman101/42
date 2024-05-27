/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:39:25 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/27 18:39:57 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"
#include "inc/mlx.h"

void	update_screen(t_screen *screen, t_map *map)
{
	map->center = map_calc_center(map->p, map->height * map->width);
	screen->offset_x = (screen->width - map->center.x) / 2;
	screen->offset_y = (screen->height- map->center.y);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		data_destroy(data);
		exit (EXIT_SUCCESS);
	}
	if (keycode == 'a')
		data->screen->angle_y -= 0.15;
	else if (keycode == 'd')
		data->screen->angle_y += 0.15;
	else if (keycode == 'w')
		data->screen->angle_x -= 0.15;
	else if (keycode == 's')
		data->screen->angle_x += 0.15;
	else if (keycode == 'q')
		data->screen->angle_z -= 0.15;
	else if (keycode == 'e')
		data->screen->angle_z += 0.15;
	else if (keycode == '-')
		data->scale -= 2.f;
	else if (keycode == '+')
		data->scale += 2.f;
	draw_projected(data);
	return (1);
}

int	print_usage()
{
	ft_printf("Wrong Usage!\n\tPlease provide a valid map");
	ft_printf("(consistent row length and valid values)\n");
	ft_printf("\tSyntax: \"./fdf example_map.fdf\"\n");
	return (1);
}

int	handle_close(t_data *data)
{
	data_destroy(data);
	exit (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    t_data		*data;

	if (argc != 2)
		exit(print_usage());
	data = data_create(argv);
	mlx_key_hook(data->win, key_press, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
	draw_projected(data);
	mlx_loop(data->mlx);
    return (0);
}
