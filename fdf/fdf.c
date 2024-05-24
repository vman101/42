/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:21:21 by victor            #+#    #+#             */
/*   Updated: 2024/05/24 19:54:44 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"
#include "inc/mlx.h"

void	map_scale(t_point3d *p, float scale, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		p[i].x *= scale;
		p[i].y *= scale;
		i++;
	}
}

void	draw_projected(t_data *data)
{

	size_t	i;
	size_t	j;

	i = 0;
	while (data->map->height > i)
	{
		j = 0;
		while (data->map->width != j)
		{
			if (j + 1 < data->map->width)
				draw_line(data, &data->map_projected[j + data->map->width * i], &data->map_projected[j + 1 + data->map->width * i]);
			if (i + 1 < data->map->height)
				draw_line(data, &data->map_projected[j + data->map->width * i], &data->map_projected[j + data->map->width * (i + 1)]);
			j++;
		}
		i++;
	}
}

void	map_copy(t_map *map, t_point3d *p)
{
	size_t i;

	i = 0;
	while (i < map->width * map->height)
	{
		p[i] = map->p[i];
		i++;
	}
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

void	update_screen(t_screen *screen, t_map *map)
{
	map->center = map_calc_center(map->p, map->height * map->width);
	screen->offset_x = (screen->width - map->center.x) / 2;
	screen->offset_y = (screen->height- map->center.y);
}

int	key_press(int keycode, t_data *data)
{
	ft_printf("%d\n", keycode);
	if (keycode == XK_Escape)
	{
		data_destroy(data);
		exit (EXIT_SUCCESS);
	}
	if (keycode == 'a')
		data->screen->angle_y -= 0.1;
	else if (keycode == 'd')
		data->screen->angle_y += 0.1;
	else if (keycode == 'w')
		data->screen->angle_x -= 0.1;
	else if (keycode == 's')
		data->screen->angle_x += 0.1;
	else if (keycode == 'q')
		data->screen->angle_z -= 0.1;
	else if (keycode == 'e')
		data->screen->angle_z += 0.1;
	mlx_clear_window(data->mlx, data->win);
	rotate_z(data->map, data->map_projected, data->screen->angle_z);
	rotate_y(data->map, data->map_projected, data->screen->angle_y);
	rotate_x(data->map, data->map_projected, data->screen->angle_x);
	printf("x: %f\ny: %f\nz: %f\n", data->screen->angle_x, data->screen->angle_y, data->screen->angle_z);
	draw_projected(data);
	map_copy(data->map, data->map_projected);
	return (1);
}

t_point2d	map_calc_center(t_point3d *p, size_t size)
{
	float	minx;
	float	maxx;
	float	miny;
	float	maxy;
	size_t	i;

	i = 0;
	minx = p[i].x;
	maxx = p[i].x;
	maxy = p[i].y;
	miny = p[i].y;
	while (i < size)
	{
		if (p[i].x < minx)
			minx = p[i].x;
		if (p[i].x > maxx)
			maxx = p[i].x;
		if (p[i].y < miny)
			miny = p[i].y;
		if (p[i].y > maxy)
			maxy = p[i].y;
		i++;
	}
	return ((t_point2d){maxx - minx, maxy - miny, 0xffffff});
}

int	print_usage()
{
	return (1);
}

t_screen	*screen_create(t_map *map)
{
	t_screen *tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->width = 800;
	tmp->height = 600;
	tmp->angle_x = 15 * M_PI / 180;
	tmp->angle_y = 110 * M_PI / 180;
	tmp->angle_z = 45 * M_PI / 180;
	tmp->offset_x = (tmp->width - map->center.x) / 2.f;
	tmp->offset_y = (tmp->height - map->center.y) / 2.f;
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
	tmp->map_projected = malloc(sizeof(t_point3d) * tmp->map->height * tmp->map->width);
	if (!tmp->map_projected)
	{
		data_destroy(tmp);
		exit(EXIT_FAILURE);
	}
	return (tmp);
}

int main(int argc, char **argv)
{
    t_data		*data;

	if (argc != 2)
		exit(print_usage());
	data = data_create(argv);
	map_scale(data->map->p, 25.f, data->map->height * data->map->width);
	map_copy(data->map, data->map_projected);
	data->screen = screen_create(data->map);
	mlx_key_hook(data->win, key_press, data);
	mlx_loop(data->mlx);
    return (0);
}
