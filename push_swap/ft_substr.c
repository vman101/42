/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:58:25 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/07 22:04:27 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

size_t	ft_strlen(char const *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	i;

	i = 0;
	if (!s || start >= ft_strlen(s) || len <= 0)
	{
		tmp = malloc(1);
		if (!tmp)
			return (NULL);
		tmp[i] = 0;
		return (tmp);
	}
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	tmp = malloc(sizeof(*tmp) * len + 1);
	if (!tmp)
		return (NULL);
	while (i < len && s[i])
	{
		tmp[i] = s[i + start];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
