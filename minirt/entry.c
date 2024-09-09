/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:33:29 by victor            #+#    #+#             */
/*   Updated: 2024/09/08 23:48:47 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	collect_position(char **entry_position, char *params[], u32 count)
{
	char	*tmp;
	u32		i;

	i = 0;
	tmp = *entry_position;
	params[i] = tmp;
	while (i < count)
	{
		tmp = ft_strchr(tmp, ',');
		if (!tmp)
			return (ft_putendl_fd("Invalid sphere configuration", 2), false);
		*tmp++ = 0;
		i++;
		params[i] = tmp;
	}
	while (*tmp && !ft_isspace((*tmp)))
		tmp++;
	if (*tmp)
		*tmp = 0;
	*entry_position = tmp + 1;
	return (true);
}

bool	collect_diameter(char **entry_position, char *params[])
{
	char	*tmp;

	tmp = *entry_position;
	while (*tmp && ft_isspace(*tmp))
		tmp++;
	if (!*tmp)
		return (ft_putendl_fd("Invalid sphere configuration: Failed in collect_diameter", 2), false);
	while (*tmp && !ft_isspace(*tmp))
		tmp++;
	*tmp = 0;
	params[0] = *entry_position;
	*entry_position = tmp + 1;
	return (true);
}

double	atod_collect_fraction(char *n, double d)
{
	bool	period;
	u32		period_positions;

	period_positions = 0;
	period = false;
	while (*n)
	{
		if (*n == '.' && period == false)
		{
			period = true;
			n++;
			continue ;
		}
		else if ((*n == '.' && period == true) \
				|| (!ft_isdigit(*n) && *n != '.'))
			return (ft_putendl_fd("Invalid double format: Too many periods", \
						2), exit(1), 0);
		if (period)
			period_positions++;
		d *= 10;
		d += (*n - '0');
		n++;
	}
	return (d / pow(10, period_positions));
}

double	ft_atod(char *n)
{
	double	d;
	i8		sign;

	if (!n)
		exit(1);
	sign = 1;
	if (*n == '-')
	{
		sign = -1;
		n++;
	}
	else if (*n == '+')
		n++;
	d = 0;
	return (atod_collect_fraction(n, d) * sign);
}

bool	parse_sphere(char *entry, t_body *body)
{
	char	*params[7];

	ft_bzero(params, sizeof(params));
	(void)body;
	while (ft_isspace(*entry))
		entry++;
	if (!collect_position(&entry, params, 2) \
		|| !collect_diameter(&entry, &params[3]) \
		|| !collect_position(&entry, &params[4], 2))
		return (ft_putendl_fd("Invalid sphere configuration", 2), false);
	body->type = BODY_SPHERE;
	body->sphere = (t_sphere){.x = ft_atod(params[0]), .y = ft_atod(params[1]), .z = ft_atod(params[2]), \
							.diameter = ft_atod(params[3]), .color = (ft_atoi(params[4]) << 16) | (ft_atoi(params[5]) << 8) | ft_atoi(params[6])};
	return (true);
}

void	body_determine(char *entry, t_body *body)
{
	char	*tmp;

	while (*entry && ft_isspace((*entry)))
		entry++;
	tmp = entry;
	while (*tmp && !ft_isspace(*tmp))
		tmp++;
	if (!*tmp)
		exit (__LINE__);
	*tmp++ = 0;
	if (ft_strncmp(entry, "sp", 2) == 0)
		parse_sphere(tmp, body);
}

void	bodies_retrieve(const char *filepath, t_body bodies[])
{
	i32		fd;
	char	buffer[1024];
	i64		bytes_read;

	ft_bzero(buffer, sizeof(buffer));
	ft_open(&fd, filepath, O_RDONLY, 0);
	bytes_read = 1;
	if (fd > 0)
		while (bytes_read > 0)
			bytes_read = ft_read(fd, buffer, 1024);
	body_determine(buffer, bodies);
	ft_printf("buffer content: %s\n", buffer);
	(void)bodies;
	ft_close(fd);
}

void	sphere_print(t_sphere sphere)
{
	printf("sphere:\nx: %f\ny: %f\nz: %f\ndia: %f\ncolor: %X", sphere.x, sphere.y, sphere.z, sphere.diameter, sphere.color);
}

void	print_body(t_body body[])
{
	u32	i;

	i = 0;
	while (body[i].type != BODY_END)
	{
		if (body[i].type == BODY_SPHERE)
			sphere_print(body[i].sphere);
		i++;
	}
}

int	key_press(int keycode, void *param)
{
	(void)param;

	if (keycode == XK_Escape)
	{
		exit (0);
	}
	return (0);
}

void	sphere_2d_draw(t_sphere sphere, void *win, void *mlx)
{
	t_point2d	current_position;
	t_point2d	circle_extremes;
	t_point2d	circle_center;
	i32	r;

	current_position.y = sphere.y;
	circle_extremes.x = round(sphere.x) + sphere.diameter;
	circle_extremes.y = round(sphere.y) + sphere.diameter;
	r = sphere.diameter / 2;
	circle_center.x = sphere.x + r;
	circle_center.y = sphere.y + r;
	while (current_position.y < circle_extremes.y)
	{
		current_position.x = sphere.x;
		while (current_position.x < circle_extremes.x)
		{
			if ((current_position.x - circle_center.x) * (current_position.x - circle_center.x) \
				+ (current_position.y - circle_center.y) * (current_position.y - circle_center.y) <= r * r)
				mlx_pixel_put(mlx, win, current_position.x, current_position.y, sphere.color);
			current_position.x++;
		}
		current_position.y++;
	}
}

int main(int argc, char **argv)
{
	t_body	bodies[MAX_BODY];
	void	*win;
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
	{
		ft_putendl_fd("Failed to init mlx", 2);
		return (1);
	}
	win = mlx_new_window(mlx, 600, 400, "window");
	(void)win;
	ft_bzero(bodies, sizeof(bodies));
	if (argc == 2)
		bodies_retrieve(argv[1], bodies);
	sphere_2d_draw(bodies[0].sphere, win, mlx);
	print_body(bodies);
	mlx_key_hook(win, key_press, NULL);
	mlx_loop(mlx);
	return (0);
}
