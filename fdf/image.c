/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:04:36 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/12 18:01:59 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

void	img_clear_background(t_data *data, t_color color)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->screen->height)
	{
		j = 0;
		while (j < data->screen->width)
		{
			img_put_pixel(data, j++, i, color);
		}
		i++;
	}
}

static void map_update(t_data *data)
{
	map_copy(data->map, data->p);
	map_scale(data->p, data, \
			data->map->height * data->map->width);
	rotate_z(data->p, data->screen->angle_z, data->size);
	rotate_y(data->p, data->screen->angle_y, data->size);
	rotate_x(data->p, data->screen->angle_x, data->size);
}

void	draw_projected(t_data *data)
{
	size_t	i;
	size_t	j;

	i = -1;
	map_update(data);
	img_clear_background(data, 0x000000);
	while (data->map->height > ++i)
	{
		j = -1;
		while (data->map->width != ++j)
		{
			if (j + 1 < data->map->width)
				draw_line(data, &data->p[j + data->map->width * i], \
						&data->p[j + 1 + data->map->width * i]);
			if (i + 1 < data->map->height)
				draw_line(data, &data->p[j + data->map->width * i], \
						&data->p[j + data->map->width * (i + 1)]);
			if (j + 1 < data->map->width && i + 1 < data->map->height && data->map->colorized == true)
				draw_line(data, &data->p[j + data->map->width * i], \
						&data->p[(j + 1) + data->map->width * (i + 1)]);
		}
	}
}

void	img_put_pixel(t_data *data, unsigned int x, \
						unsigned int y, t_color color)
{
	char	*pixel;
	int		i;

	i = data->img.bpp - 8;
	pixel = data->img.addr + (int)(y * data->img.line_len + x * \
			(data->img.bpp / 8.f));
	while (i >= 0)
	{
		if (data->img.endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (data->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
