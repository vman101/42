/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:34:08 by victor            #+#    #+#             */
/*   Updated: 2024/09/08 23:44:11 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h> 
# include <unistd.h>
# include <math.h>
# include "types.h"
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "memory/memory.h"
# include <stdbool.h>
# include <X11/keysym.h>

# define MAX_BODY 16

typedef struct s_point2d
{
	i32	x;
	i32	y;
	u32	color;
}	t_point2d;

typedef enum e_type
{
	BODY_END = 0,
	BODY_SPHERE,
}	t_type;


typedef struct s_sphere
{
	double	diameter;
	double	x;
	double	y;
	double	z;
	u32		color;
	u32		place_holder;
}	t_sphere;

typedef struct s_body
{
	t_type	type;
	union
	{
		t_sphere	sphere;
	};
}	t_body;

/* Utils */
void	ft_open(int *fd, const char *path, int flag, int permissons);
int		ft_close(int fd);
int		ft_read(int fd, char *character, unsigned int size_to_read);

#endif
