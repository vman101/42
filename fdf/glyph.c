/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:29:23 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/13 13:48:52 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

char	**get_glyph(int fd)
{
	char	*buf;
	char	**glyph;
	size_t	i;

	glyph = ft_calloc(7, sizeof(*glyph));
	if (!glyph)
		return (NULL);
	i = 0;
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf || *buf == '#')
		{
			ft_free((void **)&buf);
			break ;
		}
		glyph[i++] = buf;
	}
	return (glyph);
}

char	***glyphs_create(char const *path)
{
	char	***glyphs;
	size_t	i;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	glyphs = ft_calloc(NUM_LET, sizeof(*glyphs));
	if (!glyphs)
		return (NULL);
	i = 0;
	while (i < NUM_LET)
	{
		glyphs[i] = get_glyph(fd);
		if (!glyphs[i++])
			return (NULL);
	}
	close(fd);
	get_next_line(-1);
	return (glyphs);
}

void	glyph_draw(t_data *data, t_point3d *begin, char const **glyph)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i / 2 < 7)
	{
		j = 0;
		while (j / 2 < 6)
		{
			if (glyph[i / 2][j] == '1')
			{
				mlx_pixel_put(data->mlx, data->win, \
						begin->x + j, begin->y + i, 0xffffff);
				mlx_pixel_put(data->mlx, data->win, \
						begin->x + j + 1, begin->y + i, 0xffffff);
				mlx_pixel_put(data->mlx, data->win, \
						begin->x + j, begin->y + i + 1, 0xffffff);
				mlx_pixel_put(data->mlx, data->win, \
						begin->x + j + 1, begin->y + i + 1, 0xffffff);
			}
			j += 2;
		}
		i += 2;
	}
}

static int	glyph_which(t_point3d *begin, char const c)
{
	if (ft_isalpha(c))
		return (begin->x += 12, c - 97);
	if (c == ':')
		return (begin->x += 12, 26);
	if (c == '+')
		return (begin->x += 12, 27);
	if (c == '-')
		return (begin->x += 12, 28);
	if (c == '=')
		return (begin->x += 12, 29);
	if (c == '\n')
		return (begin->y += 16, -1);
	return (begin->x += 12, -2);
}

void	glyph_print(t_point3d *begin, char const *text, t_data *data)
{
	size_t	i;
	int		x;
	int		index;

	x = begin->x;
	i = 0;
	while (text[i])
	{
		index = glyph_which(begin, text[i]);
		if (index >= 0)
			glyph_draw(data, begin, (char const **)data->glyph[index]);
		else if (index == -1)
			begin->x = x;
		i++;
	}
}
