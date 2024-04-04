/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:36:41 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/04 18:31:21 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s1, char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	if (!*s2)
		return (s1);
	i = 0;
	while (i < n && s1[i])
	{
		j = 0;
		if (s1[i + j] == s2[j])
		{
			while (s1[i + j] == s2[j] && s1[i + j] && i + j < n)
				j++;
			if (!s2[j])
				return (&s1[i]);
		}
		i++;
	}
	return (NULL);
}
