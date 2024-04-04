/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:44:00 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/04 14:24:24 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	char				*tmp;
	unsigned long		i;

	if (!n || !s)
		return (NULL);
	i = 0;
	tmp = malloc(n * s);
	while (i < n * s)
		tmp[i++] = 0;
	return ((void *)tmp);
}
