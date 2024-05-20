/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:21:36 by victor            #+#    #+#             */
/*   Updated: 2024/05/19 12:51:54 by victor           ###   ########.fr       */
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

typedef int t_color;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	t_color		color;
}				t_point;

typedef struct s_map
{
	char		***grid;
	t_point		*p;
	size_t		size;
	int			scale;
}				t_map;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
} t_data;

void	map_translate(t_map *map);
#endif
