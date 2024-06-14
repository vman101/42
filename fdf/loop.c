/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:27:50 by vvobis            #+#    #+#             */
/*   Updated: 2024/06/14 18:45:27 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fdf.h"

int	print_usage(void)
{
	ft_printf("Wrong Usage!\n\tPlease provide a valid map");
	ft_printf("(consistent row length and valid values)\n");
	ft_printf("\tColor values in hex from: 0x0 to 0xffffff\n");
	ft_printf("\tSyntax: \"./fdf example_map.fdf\"\n");
	return (1);
}

int	handle_close(t_data *data)
{
	data_destroy(data);
	exit (EXIT_SUCCESS);
}

void	draw_menu(t_data *data)
{
	t_point3d	begin;

	begin = (t_point3d){data->screen->width / 20.f, \
						data->screen->height / 20.f, 0, 0};
	glyph_print(&begin, "commands:\n\na: angle_y++\nd: angle_y++\n", data);
	glyph_print(&begin, "w: angle_x--\ns: angle_x++\n", data);
	glyph_print(&begin, "q: angle_z--\ne: angle_z++\n", data);
	glyph_print(&begin, "up: move_up\ndown: move_down\n", data);
	glyph_print(&begin, "left: move_left\nright: move_right\n", data);
	glyph_print(&begin, "-: zoom_out\n=: zoom_in\n", data);
}
