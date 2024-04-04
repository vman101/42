/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:36:41 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/03 15:56:02 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(char *s1, char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while(i < n && s1[i])
	{
		j = 0;
		if (s1[i + j] == s2[j] || !s2[j])
		{
			while (s1[i + j] == s2[j] && s2[j])
				j++;
			return (&s1[i]);
		}
		i++;
	}
	return (NULL);
}
