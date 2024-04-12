/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:30:35 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/07 17:54:40 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char const *s)
{
	while (*s)
		if (c == *s++)
			return (1);
	return (0);
}

int	find_end(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (*s1)
		s1++;
	while (is_set(*--s1, set))
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	if (!set)
		return (ft_substr(NULL, 0, 0));
	while (is_set(*s1, set) && *s1)
		s1++;
	if (ft_strlen((char *)s1) > find_end(s1, set))
		return (ft_substr((char *)s1, 0,
				ft_strlen((char *)s1) - find_end(s1, set)));
	else
		return (ft_substr(NULL, 0, 0));
}
