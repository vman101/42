/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:20:17 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/18 09:28:37 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*buffer_extend(void *ptr_old, size_t size_new, size_t size_old)
{
	void	*ptr_new;
	void	*ptr_back;
	void	*ptr_old_free;

	ptr_new = ft_calloc(size_new + 1, 1);
	if (!ptr_new)
		return (free(ptr_old), ptr_old = NULL, NULL);
	ptr_back = ptr_new;
	ptr_old_free = ptr_old;
	while (size_old--)
		*(char *)ptr_new++ = *(char *)ptr_old++;
	return (free(ptr_old_free), ptr_old_free = NULL, ptr_back);
}

char	*handle_no_nl(char **buf, char **left)
{
	if (left)
	{
		free(*left);
		*left = NULL;
	}
	if (!buf)
		return (NULL);
	if (ft_strlen(*buf))
		return (*buf);
	free(*buf);
	*buf = NULL;
	return (NULL);
}

char	*line_extract(char **buf_joined, char **left, size_t line_len)
{
	char	*line;

	line = ft_substr(*buf_joined, 0, line_len);
	if (!line)
		return (free(*buf_joined), *buf_joined = NULL, NULL);
	*left = ft_substr(*buf_joined, line_len, ft_strlen(*buf_joined) - line_len);
	free(*buf_joined);
	*buf_joined = NULL;
	if (!*left)
		return (free(line), line = NULL, NULL);
	return (line);
}

char	*line_handle(char **buf_fetch, int fd)
{
	char		*buf_joined;
	size_t		line_len;
	static char	*left[MAX_FD];

	if (!buf_fetch)
		return (handle_no_nl(NULL, &left[fd]));
	buf_joined = ft_strjoin(left[fd], *buf_fetch);
	free(*buf_fetch);
	*buf_fetch = NULL;
	free(left[fd]);
	left[fd] = NULL;
	if (!buf_joined)
		return (NULL);
	line_len = find_newline(buf_joined);
	if (line_len)
		return (line_extract(&buf_joined, &left[fd], line_len));
	return (handle_no_nl(&buf_joined, &left[fd]));
}

char	*get_next_line(int fd)
{
	char		*buf[MAX_FD];
	ssize_t		bytes_read;
	size_t		buf_size_cur;
	size_t		buf_size_prev;

	if (fd < 0)
		return (NULL);
	buf[fd] = ft_calloc(sizeof(*buf[fd]), BUFFER_SIZE + 1);
	buf_size_prev = 0;
	buf_size_cur = BUFFER_SIZE;
	while (1)
	{
		if (!buf[fd])
			return (line_handle(NULL, fd));
		bytes_read = read(fd, buf[fd] + buf_size_prev, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf[fd]), buf[fd] = NULL, line_handle(NULL, fd));
		if (find_newline(buf[fd]) || bytes_read == 0)
			break ;
		buf_size_prev = buf_size_cur;
		buf_size_cur += BUFFER_SIZE;
		buf[fd] = buffer_extend(buf[fd], buf_size_cur, buf_size_prev);
	}
	return (line_handle(&buf[fd], fd));
}
