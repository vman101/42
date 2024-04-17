/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:14:13 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/17 10:59:28 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(ft_strlen(s) + 1, sizeof(*tmp));
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	free(s);
	return (tmp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*tmp;
	unsigned int	i;
	unsigned int	j;

	if (!s1)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (NULL);
	tmp = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(*tmp));
	if (!tmp)
		return (free(s1), free(s2), NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			tmp[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
		while (s2[j])
			tmp[i++] = s2[j++];
	free (s1);
	return (tmp);
}

void	*ft_calloc(size_t n, size_t s)
{
	void	*ptr_new;
	void	*ptr_back;
	size_t	i;

	if (n == 0)
		return (malloc(0));
	if (SIZE_MAX / n < s)
		return (NULL);
	ptr_new = malloc(n * s);
	if (!ptr_new)
		return (NULL);
	i = 0;
	ptr_back = ptr_new;
	while (i++ < s * n)
		*(char *)ptr_new++ = 0;
	return (ptr_back);
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
	tmp = ft_calloc(len + 1, sizeof(*tmp));
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
