/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:58:25 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/05 18:55:48 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	i;

	tmp = malloc(sizeof(*tmp) * len + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	if (s == NULL || (int)start >= ft_strlen(s) || len <= 0)
	{
		tmp[i] = 0;
		return (tmp);
	}
	while (i < len)
	{
		tmp[i] = s[i + start];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
