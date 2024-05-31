/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:36:53 by victor            #+#    #+#             */
/*   Updated: 2024/05/31 12:57:21 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

t_screen	*screen_create(t_map *map, float scale)
{
	t_screen	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->width = map->width * scale * 2;
	if (tmp->width > 1920)
		tmp->width = 1920;
	tmp->height = map->height * scale * 2;
	if (tmp->height > 1080)
		tmp->height = 1080;
	tmp->angle_x = 30 * M_PI / 180;
	tmp->angle_y = 120 * M_PI / 180;
	tmp->angle_z = 30 * M_PI / 180;
	tmp->offset_x = (tmp->width) / 2.f;
	tmp->offset_y = (tmp->height) / 2.f;
	return (tmp);
}

t_data	*data_create(char **argv)
{
	t_data	*tmp;

	tmp = ft_calloc(1, sizeof(*tmp));
	if (!tmp)
		exit(EXIT_FAILURE);
	tmp->map = map_create(argv[1]);
	if (!tmp->map)
		exit(data_destroy(tmp));
	tmp->scale = (((float)MAX_WIDTH / 2.f) / (float)(tmp->map->width));
	tmp->screen = screen_create(tmp->map, tmp->scale);
	if (!tmp->screen)
		exit(data_destroy(tmp));
	tmp->mlx = mlx_init();
	if (!tmp->mlx)
		exit(data_destroy(tmp));
	tmp->win = mlx_new_window(tmp->mlx, tmp->screen->width, \
			tmp->screen->height, "Line");
	if (!tmp->win)
		exit(data_destroy(tmp));
	tmp->size = tmp->map->width * tmp->map->height;
	tmp->p = malloc(sizeof(t_point3d) * tmp->size);
	if (!tmp->p)
		exit(data_destroy(tmp));
	return (tmp);
}

int	data_destroy(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->mlx && data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->screen);
		free(data->mlx);
	}
	if (data->map)
	{
		free(data->map->p);
		free(data->map);
		free(data->p);
	}
	if (data->glyph)
		glyph_destroy(data->glyph);
	free(data);
	return (1);
}

void	glyph_destroy(char ***glyph)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < NUM_LET)
	{
		j = 0;
		while (j < 7)
			free(glyph[i][j++]);
		free(glyph[i++]);
	}
	free(glyph);
}
