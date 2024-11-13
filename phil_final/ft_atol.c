/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:49:04 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/16 17:23:47 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static unsigned char	is_space(char s)
{
	return (s == ' ' || (s > 9 && s < 14));
}

long	ft_atol(char const *s, unsigned char *too_big)
{
	long long	nb;
	char const	*tmp;

	nb = 0;
	while (is_space(*s))
		s++;
	tmp = s;
	if (*tmp == '+' || *tmp == '-')
		tmp++;
	while (*tmp >= '0' && *tmp <= '9')
	{
		nb *= 10;
		nb += (*tmp - '0');
		tmp++;
		if (nb > INT_MAX || nb < INT_MIN)
			return (*too_big = 1);
	}
	if (*s == '-')
		nb = -nb;
	return (nb);
}
