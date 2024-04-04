/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:58:25 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/04 19:24:29 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	i;

	tmp = malloc(ft_strlen(s) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp[i] = s[i + start - 1];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
