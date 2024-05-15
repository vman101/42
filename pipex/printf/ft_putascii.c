/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:54:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/15 10:00:33 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_putchar(int c, int *count)
{
	write(1, &c, 1);
	*count += 1;
}

void	p_putnbr(long n, int *count)
{
	if (n < 0)
		p_putchar(0x2d, count);
	if (n <= -10)
		p_putnbr(n / -10, count);
	if (n >= 10)
		p_putnbr(n / 10, count);
	if (n >= 0)
		p_putchar(n % 10 + 0x30, count);
	if (n < 0)
		p_putchar(-(n % -10) + 0x30, count);
}

void	p_putstr(const char *str, int *count)
{
	if (!str)
	{
		*count += p_printf("(null)");
		return ;
	}
	while (*str)
		p_putchar(*str++, count);
}
