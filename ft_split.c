/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:15:38 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/05 19:27:55 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int count(char const *s, char c)
{
	unsigned int n;
	unsigned int i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if(s[i] == c && s[i + 1] != c)
			n++;
		i++;
	}
	if (n == 0)
		return (1);
	return(n);
}

char	**ft_split(char const *s, char c)
{
	char **tmp;
	char **back;
	int j;
	
	tmp = malloc(sizeof(*tmp) * count(s, c) + 1);
	if (!tmp || !s)
		return (NULL);
	back = tmp;
	if (c == 0)
		*tmp = 0;
	while (*s)
	{
		j = 0;
		while (s[j] != c && s[j])
			j++;
		if (j)
			*tmp++ = ft_substr((char *)s, 0, j);
		else
			j = 1;
		s += j;
	}
	return (back);
}
