/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:21:21 by victor            #+#    #+#             */
/*   Updated: 2024/05/25 13:59:06 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"
#include "inc/mlx.h"
#include <math.h>

void matrix_multiply(t_mat res, t_mat a, t_mat b)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			k = -1;
			((float **)&res)[i][k + 1] = 0;
			while (++k < 3)
				((float **)&res)[i][j] += ((float **)&a)[i][k] * ((float **)&b)[k][j];
		}
	}
}

t_mat	matrix_create_x(float theta)
{
	float	cos_t;
	float	sin_t;
	t_mat	mat;

	cos_t = cosf(theta);
	sin_t = sinf(theta);
	mat = (t_mat){	{1,		0,		0},
					{0, cos_t, -sin_t},
					{0, sin_t,	cos_t}
				};
	return (mat);
}

t_mat	matrix_create_y(float theta)
{
	float	cos_t;
	float	sin_t;
	t_mat	mat;

	cos_t = cosf(theta);
	sin_t = sinf(theta);
	mat = (t_mat){	{cos_t, 0,	sin_t},
					{0,		1,		0},
					{-sin_t, 0, cos_t}
				};
	return (mat);
}

t_mat	matrix_create_z(float theta)
{
	float	cos_t;
	float	sin_t;
	t_mat	mat;

	cos_t = cosf(theta);
	sin_t = sinf(theta);
	mat = (t_mat){	{cos_t,	-sin_t,	0},
					{sin_t,	 cos_t,	0},
					{0,		 0,		1}
				};
	return (mat);
}

void matrices_create(t_mat new[3], float theta_x, float theta_y, float theta_z)
{
	new[X] = matrix_create_x(theta_x);
	new[Y] = matrix_create_y(theta_y);
	new[Z] = matrix_create_z(theta_z);
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
	map_copy(data->map, data->map_projected);
	map_scale(data->map_projected, data->screen, 15.f, data->size);
	rotate_z(data->map, data->map_projected, data->screen->angle_z);
	rotate_y(data->map, data->map_projected, data->screen->angle_y);
	rotate_x(data->map, data->map_projected, data->screen->angle_x);
	printf("x: %f\ny: %f\nz: %f\n", data->screen->angle_x, data->screen->angle_y, data->screen->angle_z);
	map_print(data->map_projected, data->size);
	point_print(&data->map->center);
	draw_projected(data);
	return (1);
}

int	print_usage()
{
	return (1);
}

int main(int argc, char **argv)
{
    t_data	*data;
	t_mat	new[3];

	if (argc != 2)
		exit(print_usage());
	data = data_create(argv);
	data->screen = screen_create(data->map);
	matrices_create(new, M_PI / 4, M_PI / 4, M_PI / 4);
	mlx_key_hook(data->win, key_press, data);
	mlx_loop(data->mlx);
    return (0);
}
