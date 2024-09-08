/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:50:35 by victor            #+#    #+#             */
/*   Updated: 2024/09/08 17:10:32 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_read(int fd, char *character, unsigned int size_to_read)
{
	int	bytes_read;

	bytes_read = read(fd, character, size_to_read);
	if (bytes_read == -1)
	{
		perror("read");
	}
	return (bytes_read);
}

int	ft_close(int fd)
{
	if (fd == -1)
		return (0);
	if (close(fd) == -1)
	{
		perror("close");
	}
	return (1);
}

/* flag corresponds to O_RDONLY, O_CREAT etc.; 
 * When opening a file, permissions doesnt can be set to 0*/
void	ft_open(int *fd, const char *path, int flag, int permissons)
{
	if (permissons > 0)
		*fd = open(path, flag, permissons);
	else
		*fd = open(path, flag);
	if (*fd == -1)
	{
		perror("open");
	}
}
