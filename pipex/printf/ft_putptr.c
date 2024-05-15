/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:53:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/15 10:01:15 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_putptr(void *ptr, int *count)
{
	void	**to_print;

	if (!ptr)
	{
		*count += p_printf("(nil)");
		return ;
	}
	to_print = &ptr;
	*count += p_printf("0x");
	p_puthex_lower((long)*to_print, count);
}
