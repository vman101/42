/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:09:57 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/15 20:10:04 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_newline(char *buf)
{
	size_t	i;

	if (!buf)
		return (0);
	i = 0;
	while (*buf)
	{
		if (*buf == '\n')
			return (i + 1);
		i++;
		buf++;
	}
	return (0);
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

void	*buffer_extend(void *ptr_old, size_t size_new, size_t size_old)
{
	void	*ptr_new;
	void	*ptr_back;
	void	*ptr_old_free;

	ptr_new = ft_calloc(size_new + 1, 1);
	if (!ptr_new)
		return (NULL);
	ptr_back = ptr_new;
	ptr_old_free = ptr_old;
	ft_memcpy(ptr_new, ptr_old, size_old);
	free(ptr_old_free);
	return (ptr_back);
}

char	*handle_no_nl(char **buf)
{
	if (ft_strlen(*buf))
		return (*buf);
	free(*buf);
	return (NULL);
}


char	*line_extract(char **buf_fetch)
{
	static char	*left;
	char		*buf_joined;
	char		*line;
	size_t		line_len;

	buf_joined = ft_strjoin(left, *buf_fetch);
	free(*buf_fetch);
	line_len = find_newline(buf_joined);
	if (line_len)
	{
		line = ft_substr(buf_joined, 0, line_len);
		if (!line)
			return (NULL);
		free(left);
		left = ft_strdup(buf_joined + line_len);
		free(buf_joined);
		if (!left)
			return (NULL);
		return (line);
	}
	free(left);
	left = NULL;
	return (handle_no_nl(&buf_joined));
}

char	*get_next_line(int fd)
{
	char		*buf_fetch;
	ssize_t		bytes_read;
	size_t		buf_size_cur;
	size_t		buf_size_prev;

	buf_fetch = ft_calloc(sizeof(*buf_fetch), BUFFER_SIZE + 1);
	buf_size_prev = 0;
	buf_size_cur = BUFFER_SIZE;
	while (1)
	{
		if (!buf_fetch)
			return (NULL);
		bytes_read = read(fd, buf_fetch + buf_size_prev, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf_fetch);
			return (NULL);
		}
		if (find_newline(buf_fetch))
			break ;
		if (bytes_read == 0)
			break ;
		buf_size_cur += BUFFER_SIZE;
		buf_size_prev += BUFFER_SIZE;
		buf_fetch = buffer_extend(buf_fetch, buf_size_cur + 1, buf_size_prev);
	}
	return (line_extract(&buf_fetch));
}

/*
int main()
{
	char	*input_line;
	int		input;
	int		output;

	input = open("./input", O_RDONLY);
	output = open("./output", O_WRONLY);

	while (1)
	{
		input_line = get_next_line(input);
		write(output, input_line, ft_strlen(input_line));
		free(input_line);
		if (!input_line)
			break ;
	}
	close(input);
	close(output);
} */
