/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:36:53 by victor            #+#    #+#             */
/*   Updated: 2024/05/25 12:39:11 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

t_screen	*screen_create(t_map *map)
{
	t_screen *tmp;

	(void)map;
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->width = 800;
	tmp->height = 600;
	tmp->angle_x = 15 * M_PI / 180;
	tmp->angle_y = 110 * M_PI / 180;
	tmp->angle_z = 45 * M_PI / 180;
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
    tmp->mlx = mlx_init();
    if (!tmp->mlx)
		exit(EXIT_FAILURE);
    tmp->win = mlx_new_window(tmp->mlx, 800, 600, "Line");
    if (!tmp->win)
	{
		data_destroy(tmp);
		exit(EXIT_FAILURE);
	}
	tmp->map = map_create(argv[1]);
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
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	map_destroy(data->map);
	free(data->map_projected);
	free(data->screen);
	free(data);
}
