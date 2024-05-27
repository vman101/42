/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:21:36 by victor            #+#    #+#             */
/*   Updated: 2024/05/25 13:20:57 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <float.h>

enum	e_vertex
{
	X,
	Y,
	Z
};

typedef int t_color;

typedef struct	s_mat
{
	float	x[3];
	float	y[3];
	float	z[3];
}				t_mat;

typedef struct	s_point3d
{
	float			x;
	float			y;
	float			z;
	t_color		color;
}				t_point3d;

typedef struct s_point2d
{
	float		x;
	float		y;
	t_color		color;
}				t_point2d;

typedef struct s_map
{
	t_point3d	*p;
	t_point3d	center;
	size_t		width;
	size_t		height;
}				t_map;

typedef struct s_screen
{
	size_t	width;
	size_t	height;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	size_t	offset_x;
	size_t	offset_y;
}
t_screen;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_point3d	*map_projected;
	t_screen	*screen;
	size_t		size;
	float		scale;
} t_data;

/* Setup */

t_screen	*screen_create(t_map *map);
t_data	*data_create(char **argv);
void	data_destroy(t_data *data);

/* Map Creation */

int	get_split_len(char const **split);
int	get_row_len(char const ***row);
int map_get_rows(char const *path, char ****row);
int	map_atoi(char const *s, int b);
t_map	*map_create(char const *path);
void	map_points_create(char ****points, t_map *map);
void	map_destroy(t_map *map);
t_point2d point2d_create(float x, float y, t_color color);
t_point3d point3d_create(float x, float y, float z, t_color color);

/* Debug */

void	point_print(t_point3d *p);
void	map_print(t_point3d *p, size_t size);

/* Rotation */

void	rotate_x(t_map *map, t_point3d *p, float theta);
void	rotate_z(t_map *map, t_point3d *p, float theta);
void	rotate_y(t_map *map, t_point3d *p, float theta);
t_point3d	map_calc_center(t_point3d *p, size_t size);
void	substract_center(t_point3d *p, t_point3d *center, size_t size);
void	map_copy(t_map *map, t_point3d *p);
void	map_scale(t_point3d *p, t_screen *screen, float scale, size_t size);

/* Drawing */

void	draw_projected(t_data *data);
void draw_line(t_data *data, t_point3d *begin, t_point3d *end);

#endif
