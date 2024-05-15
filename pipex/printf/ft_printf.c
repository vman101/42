/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:35 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/15 11:15:34 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_arg(va_list args, char format, int *count)
{
	if (format == 'd' || format == 'i')
		p_putnbr(va_arg(args, int), count);
	else if (format == 'u')
		p_putnbr(va_arg(args, unsigned int), count);
	else if (format == 's')
		p_putstr(va_arg(args, char *), count);
	else if (format == 'X')
		p_puthex_upper(va_arg(args, unsigned int), count);
	else if (format == 'x')
		p_puthex_lower(va_arg(args, unsigned int), count);
	else if (format == 'p')
		p_putptr(va_arg(args, void *), count);
	else if (format == 'c')
		p_putchar(va_arg(args, int), count);
	else if (format == '%')
		p_putchar('%', count);
	else
		return (0);
	return (1);
}

int	p_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (1)
	{
		while (*format != '%' && *format)
			p_putchar(*format++, &count);
		if (!*format)
			break ;
		else
			format++;
		if (!*format || !handle_arg(args, *format, &count))
			return (-1);
		format++;
	}
	va_end(args);
	return (count);
}
