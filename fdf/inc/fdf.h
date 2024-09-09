/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:21:36 by victor            #+#    #+#             */
/*   Updated: 2024/06/14 13:29:19 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include "../libft/libft.h"
# include <mlx.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define NUM_LET 30
# define TOLERANCE 0.0001f

typedef unsigned int	t_color;

enum	e_modes
{
	MAX = 0,
	SINGLE = 1
};

typedef struct s_point3d
{
	float		x;
	float		y;
	float		z;
	t_color		color;
}				t_point3d;

typedef struct s_map
{
	t_point3d	*p;
	t_point3d	center;
	size_t		width;
	size_t		height;
	size_t		size;
	bool		colorized;
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
}			t_screen;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		*map;
	t_point3d	*p;
	t_screen	*screen;
	size_t		size;
	char		***glyph;
	float		scale;
	float		scale_z;
}				t_data;
/* Statics */

/*
static void		draw_point(t_data *data, t_point3d *point, t_color color);
static void		calculate_line(float *err, t_point3d *begin, \
							t_point3d *move, t_point3d *end);
static t_screen	*screen_create(t_map *map, float scale);
static void		destroy_points(char ****points, int i);
static void		img_clear_background(t_data *data, t_color color);
*/

/* Setup */

void		*data_create(t_data *data, char const **argv);
int			data_destroy(t_data *data);

/* Map Creation */

int			get_split_len(char const **split);
int			get_row_len(char const ****row, int mode);
int			map_get_rows(char const *path, char ****row, bool *flag);
t_map		*map_create(char const *path);
void		map_colors_correct(t_map *map);

/* Debug */

int			print_usage(void);
void		point_print(t_point3d *p);
void		map_print(t_point3d *p, size_t size);
int			handle_close(t_data *data);

/* Rotation */

void		rotate_x(t_point3d *p, float theta, size_t size);
void		rotate_y(t_point3d *p, float theta, size_t size);
void		rotate_z(t_point3d *p, float theta, size_t size);
t_point3d	map_calc_center(t_point3d *p, size_t size);
void		substract_center(t_point3d *p, t_point3d *center, size_t size);
void		map_copy(t_map *map, t_point3d *p);
void		map_scale(t_point3d *p, t_data *data, size_t size);

/* Drawing */

void		draw_projected(t_data *data, t_map *map);
void		draw_line(t_data *data, t_point3d begin, t_point3d end);
t_color		line_color(t_color s, t_color e, float ratio);

/* Glyphs */

/*static char		**get_glyph(int fd, bool *flag);*/
char		***glyphs_create(char const *path);
void		glyph_draw(t_data *data, t_point3d *begin, char const **glyph);
void		glyph_print(t_point3d *begin, char const *text, t_data *data);
void		glyph_destroy(char ***glyph);
void		draw_menu(t_data *data);

/* Image */

void		img_put_pixel(t_data *data, unsigned int x, \
							unsigned int y, t_color color);
void		img_clear_background(t_data *data, t_color color);
#endif
