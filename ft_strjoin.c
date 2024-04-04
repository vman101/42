/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:08:03 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/04 19:24:02 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*tmp;
	unsigned int	i;
	unsigned int	j;

	tmp = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		tmp[i] = s2[j];
		i++;
		j++;
	}
	tmp[i] = 0;
	return (tmp);
}
