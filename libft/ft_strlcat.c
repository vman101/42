/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:04:09 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/02 19:11:35 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcat(char *dest, char *src, size_t size)
{
	int	i;

	i = 0;
	while (dest[i])
		i++;
	if (i < (int)size)
	{
		while(i < (int)size && *src)
		{
			dest[i] = *src++;
			i++;
		}
	}
	dest[i] = 0;
	return (ft_strlen(dest) + ft_strlen(src));
}
