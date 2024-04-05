/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:14:20 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/05 20:15:51 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	count(char const *s, char c)
{
	unsigned int	n;
	unsigned int	i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			n++;
		i++;
	}
	if (n == 0)
		return (1);
	return (n);
}

int	is_split(char const c, char s)
{
	if (c == s)
		return (1);
	return (0);
}

char	*copy_word(char const *s, char split)
{
	int	i;

	i = 0;
	while (!is_split(s[i], split))
		i++;
	return (ft_substr((char *)s, 0, i));
}

char	**ft_split(char const *s, char c)
{
	char	**tmp;
	char	**back;
	int		j;

	if (!s)
		return (NULL);
	tmp = malloc(sizeof(*tmp) * count(s, c) + 1);
	if (!tmp)
		return (NULL);
	back = tmp;
	if (c == 0)
		*tmp = 0;
	while (1)
	{
		j = 0;
		if (!*s)
			break ;
		while (is_split(*s, c) && *s)
			s++;
		if (*s)
			*tmp++ = copy_word(s, c);
		while (!is_split(*s, c) && *s)
			s++;
	}
	return (back);
}
