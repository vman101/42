/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:39:25 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/15 16:24:07 by vvobis           ###   ########.fr       */
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
		data->screen->offset_y -= 20;
	else if (keycode == XK_Right)
		data->screen->offset_x += 20;
	else if (keycode == XK_Left)
		data->screen->offset_x -= 20;
	else if (keycode == XK_Down)
		data->screen->offset_y += 20;
	else if (keycode == '=')
	{
		data->scale += data->scale / 4;
		data->scale += data->scale / 4;
		data->scale_z += data->scale_z / 4;
	}
	else if (keycode == '-')
	{
		data->scale -= data->scale / 4;
		data->scale -= data->scale / 4;
		data->scale_z -= data->scale_z / 4;
	}
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
	draw_projected(data, data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_menu(data);
	img_clear_background(data, 0x000000);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_img	img;

	if (argc != 2 || !ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) \
			|| *(ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) + 4) != 0)
		exit(print_usage());
	data = ft_calloc(1, sizeof(*data));
	if (!data)
		exit(EXIT_FAILURE);
	data_create(data, (char const **)argv);
	img.img = mlx_new_image(data->mlx, data->screen->width, \
			data->screen->height);
	if (!img.img)
		exit(data_destroy(data));
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	data->img = img;
	draw_projected(data, data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_menu(data);
	mlx_key_hook(data->win, key_press, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_loop(data->mlx);
	return (0);
}
