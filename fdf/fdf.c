/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:39:25 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/31 13:25:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

int	key_press_handle(int keycode, t_data *data)
{
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
	else
		return (0);
	return (1);
}

void	key_press_handle2(int keycode, t_data *data)
{
	if (keycode == XK_Up)
		data->screen->offset_y -= 2 * data->scale;
	else if (keycode == XK_Right)
		data->screen->offset_x += 2 * data->scale;
	else if (keycode == XK_Left)
		data->screen->offset_x -= 2 * data->scale;
	else if (keycode == XK_Down)
		data->screen->offset_y += 2 * data->scale;
	else if (keycode == '=')
		data->scale += data->scale / 4;
	else if (keycode == '-')
		data->scale -= data->scale / 4;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		data_destroy(data);
		exit (EXIT_SUCCESS);
	}
	if (!key_press_handle(keycode, data))
		key_press_handle2(keycode, data);
	draw_projected(data);
	draw_menu(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_img	img;

	if (argc != 2)
		exit(print_usage());
	data = data_create(argv);
	img.img = mlx_new_image(data->mlx, data->screen->width, \
			data->screen->height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	data->img = img;
	data->glyph = glyphs_create("alpha.bit");
	if (!data->glyph)
		exit(data_destroy(data));
	mlx_key_hook(data->win, key_press, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
	draw_projected(data);
	mlx_loop(data->mlx);
	return (0);
}
