/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:10:59 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/04 17:08:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	dlen;
	unsigned int	slen;

	if (size == 0)
		return (ft_strlen(src));
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (slen + size);
	if (dlen + slen < size)
	{
		ft_memcpy(&dest[dlen], src, slen);
		dest[dlen + slen] = 0;
	}
	else
	{
		ft_memcpy(&dest[dlen], src, size - dlen);
		dest[size - 1] = 0;
	}
	return (dlen + slen);
}
