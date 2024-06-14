/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:36:53 by victor            #+#    #+#             */
/*   Updated: 2024/06/14 18:24:49 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

static t_screen	*screen_create(t_map *map, float scale)
{
	t_screen	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->width = scale * (float)(map->width);
	if (tmp->width > 1920)
		tmp->width = 1920;
	tmp->height = scale * (float)(map->height);
	if (tmp->height > 1080)
		tmp->height = 1080;
	tmp->angle_x = 30 * M_PI / 180;
	tmp->angle_y = 130 * M_PI / 180;
	tmp->angle_z = 30 * M_PI / 180;
	tmp->offset_x = (tmp->width) / 2.f;
	tmp->offset_y = (tmp->height) / 2.f;
	return (tmp);
}

void	*data_create(t_data *data, char const **argv)
{
	data->map = map_create(argv[1]);
	if (!data->map)
		exit(data_destroy(data));
	data->scale = fmin((float)MAX_WIDTH / data->map->height, \
			(float)MAX_HEIGHT / data->map->width);
	data->screen = screen_create(data->map, data->scale);
	if (!data->screen)
		exit(data_destroy(data));
	data->scale /= 1.5f;
	data->scale_z = (data->scale / 4);
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(data_destroy(data));
	data->win = mlx_new_window(data->mlx, data->screen->width, \
			data->screen->height, "FDF");
	if (!data->win)
		exit(data_destroy(data));
	data->glyph = glyphs_create("alpha.bit");
	if (!data->glyph)
		exit(data_destroy(data));
	data->p = ft_calloc(data->map->size + 1, sizeof(t_point3d));
	if (!data->p)
		exit(data_destroy(data));
	return (data);
}

int	data_destroy(t_data *data)
{
	if (data->glyph)
		glyph_destroy(data->glyph);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	ft_free((void **)&data->mlx);
	ft_free((void **)&data->screen);
	if (data->map)
	{
		ft_free((void **)&data->map->p);
		ft_free((void **)&data->map);
	}
	ft_free((void **)&data->p);
	ft_free((void **)&data);
	return (1);
}

void	glyph_destroy(char ***glyph)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < NUM_LET && glyph[i])
	{
		j = 0;
		while (j < 7)
			ft_free((void **)&glyph[i][j++]);
		ft_free((void **)&glyph[i++]);
	}
	ft_free((void **)&glyph);
}
