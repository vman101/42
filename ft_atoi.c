/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:06:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/04 18:08:32 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char const *s)
{
	int	sign;
	int	res;
	int	mult;

	mult = 1;
	sign = 1;
	res = 0;
	while (*s == 0x20 || (*s >= 8 && *s <= 13))
		s++;
	if (*s == 0x2d)
		sign = -1;
	if (*s == 0x2b || *s == 0x2d)
		s++;
	while (ft_isdigit(*s))
		s++;
	while (ft_isdigit(*--s))
	{
		res += (*s - 0x30) * mult;
		mult *= 0xa;
	}
	return (res * sign);
}
