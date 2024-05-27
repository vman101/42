/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:36:53 by victor            #+#    #+#             */
/*   Updated: 2024/05/27 18:59:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

t_screen	*screen_create(t_map *map, float scale)
{
	t_screen *tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->width = map->width * scale;
	if (tmp->width > 1920)
		tmp->width = 1920;
	tmp->height = map->height * scale;
	if (tmp->height > 1080)
		tmp->height = 1080;
	tmp->angle_x = 30 * M_PI / 180;
	tmp->angle_y = 30 * M_PI / 180;
	tmp->angle_z = 30 * M_PI / 180;
	tmp->offset_x = (tmp->width) / 2.f;
	tmp->offset_y = (tmp->height) / 2.f;
	return (tmp);
}

t_data	*data_create(char **argv)
{
	t_data *tmp;

	tmp = ft_calloc(1, sizeof(*tmp));
	if (!tmp)
		exit(EXIT_FAILURE);
	tmp->map = map_create(argv[1]);
	if (!tmp->map)
	{
		data_destroy(tmp);
		exit(EXIT_FAILURE);
	}
	tmp->scale = (float)MAX_WIDTH / (float)(tmp->map->width / 2.f) / 2.f;
	tmp->screen = screen_create(tmp->map, tmp->scale);
	if (!tmp->screen)
	{
		data_destroy(tmp);
		exit(EXIT_FAILURE);
	}
    tmp->mlx = mlx_init();
    if (!tmp->mlx)
	{
		data_destroy(tmp);
		exit(EXIT_FAILURE);
	}
    tmp->win = mlx_new_window(tmp->mlx, tmp->screen->width, tmp->screen->height, "Line");
    if (!tmp->win)
	{
		data_destroy(tmp);
		exit(EXIT_FAILURE);
	}
	tmp->size = tmp->map->width * tmp->map->height;
	tmp->map_projected = malloc(sizeof(t_point3d) * tmp->size);
	if (!tmp->map_projected)
	{
		data_destroy(tmp);
		exit(EXIT_FAILURE);
	}
	return (tmp);
}

void	data_destroy(t_data *data)
{
	if (data->mlx && data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->screen);
		free(data->mlx);
	}
	if (data->map)
	{
		map_destroy(data->map);
		free(data->map_projected);
	}
	free(data);
}
