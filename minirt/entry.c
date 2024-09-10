/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:33:29 by victor            #+#    #+#             */
/*   Updated: 2024/09/10 12:54:59 by vvobis           ###   ########.fr       */
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
	body->sphere = (t_sphere){.x = ft_atod(params[0]), \
		.y = ft_atod(params[1]), .z = ft_atod(params[2]), \
		.diameter = ft_atod(params[3]), \
		.color = (0x20 << 24 | ft_atoi(params[4]) << 16) | (ft_atoi(params[5]) << 8) | ft_atoi(params[6])};
	return (true);
}

void	body_determine(char *entry, t_scene *scene)
{
	char	*tmp;

	while (*entry && ft_isspace((*entry)))
		entry++;
	tmp = entry;
	while (*tmp && !ft_isspace(*tmp))
		tmp++;
	if (!*tmp)
		return ;
	*tmp++ = 0;
	if (ft_strncmp(entry, "sp", 2) == 0)
		parse_sphere(tmp, &scene->body[scene->body_count]);
	scene->body_count += 1;
}

char	*buffer_read_chunk(t_line *line, i32 fd, bool *file_end_reached)
{
	i64		bytes_read;
	char	*tmp;

	if (!*file_end_reached)
	{
		bytes_read = ft_read(fd, line->buffer + line->length, READ_BUFFER_SIZE - line->length);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			*file_end_reached = true;
	}
	tmp = ft_strchr(line->buffer, '\n');
	if (!tmp)
	{
		tmp =  ft_strchr(line->buffer, '\0');
		if (!tmp)
			return (ft_printf("The length of line %d is too long for the current implementation\nexiting...\n", line->count), NULL);
	}
	*tmp = 0;
	line->count++;
	line->length = ft_strlen(line->buffer);
	return (tmp);
}

void	bodies_retrieve(const char *filepath, t_scene *scene)
{
	i32		fd;
	t_line	line;
	bool	file_end_reached;

	file_end_reached = false;
	ft_bzero(&line, sizeof(line));
	ft_open(&fd, filepath, O_RDONLY, 0);
	if (fd < 0)
		return ;
	while (scene->body_count != MAX_BODY - 1 && !(file_end_reached == true && line.length == 0))
	{
		if (!buffer_read_chunk(&line, fd, &file_end_reached))
			return ;
		body_determine(line.buffer, scene);
		ft_memmove(line.buffer, line.buffer + line.length + 1, READ_BUFFER_SIZE - line.length);
		line.length = ft_strlen(line.buffer);
		ft_bzero(line.buffer + line.length, READ_BUFFER_SIZE - line.length - (line.length < READ_BUFFER_SIZE));
		ft_printf("buffer content: %s\n", line.buffer);
	}
	ft_close(fd);
}

void	sphere_print(t_sphere sphere)
{
	printf("sphere:\nx: %f\ny: %f\nz: %f\ndia: %f\ncolor: %X\n", sphere.x, sphere.y, sphere.z, sphere.diameter, sphere.color);
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

int	key_press(int keycode, void *param_ptr)
{
	void	**param;

	param = param_ptr;
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(param[0], param[1]);
		mlx_destroy_display(param[0]);
		ft_free(&param[0]);
		exit (0);
	}
	return (0);
}

void	sphere_2d_draw(t_sphere sphere, void *win, void *mlx)
{
	t_point3d	current_position;
	t_point3d	circle_extremes;
	t_point3d	circle_center;
	i32			r;

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

void	bodys_draw(t_scene scene, void *win, void *mlx)
{
	u32	i;

	i = 0;
	while (i < scene.body_count)
	{
		sphere_2d_draw(scene.body[i].sphere, win, mlx);
		print_body(scene.body);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_scene	scene;
	void	*win;
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
	{
		ft_putendl_fd("Failed to init mlx", 2);
		return (1);
	}
	win = mlx_new_window(mlx, 600, 400, "window");
	ft_bzero(&scene, sizeof(scene));
	ft_bzero(scene.body, sizeof(scene.body));
	if (argc == 2)
		bodies_retrieve(argv[1], &scene);
	bodys_draw(scene, win, mlx);
	mlx_key_hook(win, key_press, (void *[2]){mlx, win});
	mlx_loop(mlx);
	return (0);
}
