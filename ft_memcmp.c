/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:27:15 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/03 15:33:04 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	char			*p1;
	char			*p2;
	unsigned int	i;

	p1 = (char *)s1;
	p2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] < p2[i])
			return (-1);
		if (p1[i] > p2[i])
			return (1);
		i++;
	}
	return (0);
}
