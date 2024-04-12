#include "get_next_line.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	char	*d;
	char	*s;

	if (n == 0 || (dest == NULL && src == NULL))
		return (dest);
	if (dest == NULL || src == NULL)
	{
		*(char *)dest = 1;
		*(char *)src = 1;
	}
	d = (char *) dest;
	s = (char *) src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*ft_calloc(size_t n, size_t s)
{
	char				*tmp;
	unsigned long		i;

	i = 0;
	if (n == 0)
		return (malloc(0));
	if (SIZE_MAX / n < s)
		return (NULL);
	tmp = malloc(n * s);
	if (tmp)
		while (i < n * s)
			tmp[i++] = 0;
	return ((void *)tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	i;

	i = 0;
	if (!s || start >= ft_strlen(s) || len <= 0)
	{
		tmp = ft_calloc(1, 1);
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
	return (tmp);
}

size_t	ft_strlen(char const *s)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	while (*s++)
		i++;
	return (i);
}
