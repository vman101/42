/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:21:21 by victor            #+#    #+#             */
/*   Updated: 2024/05/20 18:52:34 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"
#include "inc/libft.h"
#include <stdlib.h>
#include <math.h>

void draw_point(t_data *data, t_point *point, t_color color)
{
    mlx_pixel_put(data->mlx, data->win, (point->x + data->map->scale * 15) * 0.5f, point->y * 0.5f, color);
}

void	calculate_line(int *err, t_point *begin, t_point *move, t_point *end)
{
	int e2;
	int dy;
	int dx;

	dx = fabs(end->x - begin->x);
	dy = fabs(end->y - begin->y);
	e2 = *err * 2;
	if (e2 > -dy)
	{
		*err -= dy;
		if (begin->x < end->x)
			move->x++;
		else
			move->x--;
	}
	if (e2 < dx)
	{
		*err += dx;
		if (begin->y < end->y)
			move->y++;
		else
			move->y--;
	}
}

void draw_line(t_data *data, t_point *begin, t_point *end)
{
	int	err;
	t_point move;

	move = *begin;
	err = fabs(end->x - begin->x) - fabs(end->y - begin->y);
	while (move.x != end->x || move.y != end->y)
	{
		if (begin->color == 0xffffff || end->color == 0xffffff)
			draw_point(data, &move, 0xffffff);
		else
			draw_point(data, &move, begin->color);
		calculate_line(&err, begin, &move, end);
	}
	if (begin->color == 0xffffff || end->color == 0xffffff)
		draw_point(data, &move, 0xffffff);
	else
		draw_point(data, &move, begin->color);
}

int	key_press(int keycode, t_data *data)
{
	ft_printf("%d\n", keycode);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit (EXIT_SUCCESS);
	}
	return (1);
}

int	get_split_len(char const **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	get_row_len(char const ***row)
{
	int	i;

	i = 0;
	while (row[i])
		i++;
	return (i);
}

int map_get_rows(char const *path, char ****row)
{
	int	fd;
	int i;
	char *buf;
	char **tmp;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		if (row)
		{
			tmp = ft_split(buf, ' ');
			row[i] = super_split(tmp, get_split_len((char const **)tmp) + 1, ',');
			free_split(tmp);
		}
		free(buf);
		i++;
	}
	close(fd);
	return (i);
}

t_point point_create(int x, int y, int z, t_color color)
{
	t_point	p;

	p = (t_point){x, y, z, color};
	return (p);
}

void	point_print(t_point *p)
{
	ft_printf("(x: %d y: %d z: %d color: 0x%x)\n", p->x, p->y, p->z, p->color);
}

int	map_atoi_is_space(char const c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	get_nb(char c,  char *base)
{
	int	i;

	i = 0;
	while (base [i] && base[i] != c)
		i++;
	return (i);
}

int	map_atoi(char const *s, int b)
{
	int			nb;
	char const	*tmp;
	char		*base;

	if (!s)
		return (0xffffff);
	if (b == 10)
		base = "0123456789";
	else if (b == 16)
	{
		base = "0123456789abcdef";
		s += 2;
	}
	nb = 0;
	while (map_atoi_is_space(*s))
		s++;
	tmp = s;
	if (*tmp == '+' || *tmp == '-')
		tmp++;
	while (*tmp && *tmp != '\n')
	{
		nb *= b;
		nb += get_nb(*tmp, base);
		tmp++;
	}
	if (*s == '-')
		nb = -nb;
	return (nb);
}

void	map_points_create(char ****points, t_map *map)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (points[y])
	{
		x = 0;
		while (points[y][x])
		{
			map->p[i] = point_create(x * map->scale, y * map->scale, map_atoi(points[y][x][0], 10), map_atoi(points[y][x][1], 16));
			point_print(&map->p[i++]);
			x++;
		}
		y++;
	}
	i = 0;
	while (points[i])
		free_super_split(points[i++]);
}

void	map_draw(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (data->map->height > i)
	{
		j = 0;
		while (data->map->width != j)
		{
			if (data->map->p[j + data->map->width * i].y == data->map->p[j + 1 + data->map->width * i].y)
				draw_line(data, &data->map->p[j + data->map->width * i], &data->map->p[j + 1 + data->map->width * i]);
			if (i + 1 < data->map->height)
				draw_line(data, &data->map->p[j + data->map->width * i], &data->map->p[j + data->map->width * (i + 1)]);
			j++;
		}
		i++;
	}
}
                             	
void	map_print(t_map *map)	
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (map->height > i)
	{
		j = 0;
		while (map->width > j)
			point_print(&map->p[j++ + map->width * i]);
		i++;
	}
}

t_map	*map_create(char const *path)
{
	t_map	*map;
	char	****input;

	map = ft_calloc(1, sizeof(*map));
	map->height = map_get_rows(path, NULL);
	input = ft_calloc(map->height + 1, sizeof(*input));
	map_get_rows(path, input);
	map->width = get_row_len((char const ***)*input);
	map->p = ft_calloc(map->height * map->width, sizeof(*map->p));
	map->scale = 30;
	map_points_create(input, map);
	map_print(map);
	return (map);
}

void	map_destroy(t_map *map)
{
	free(map->p);
	free(map);
}

int main(int argc, char **argv)
{
    t_data data;

    data.mlx = mlx_init();
	(void)argc;
    if (!data.mlx)
		return (1);
    data.win = mlx_new_window(data.mlx, 800, 600, "Line");
    if (!data.win)
		return (1);
	data.map = map_create(argv[1]);
	mlx_key_hook(data.win, key_press, &data);
	map_draw(&data);
	mlx_loop(data.mlx);
	map_destroy(data.map);
    return (0);
}
