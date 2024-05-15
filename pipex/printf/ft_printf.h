/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:50:35 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/15 11:15:43 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		p_printf(const char *format, ...);
void	p_puthex_lower(unsigned long nbr, int *count);
void	p_puthex_upper(unsigned long nbr, int *count);
void	p_putchar(int c, int *count);
void	p_putnbr(long n, int *count);
void	p_putstr(const char *str, int *count);
void	p_putptr(void *ptr, int *count);

#endif
