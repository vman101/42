/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:25 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/15 13:45:57 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

ssize_t input_content_find(char const *buf, int c)
{
	ssize_t	ret;

	ret = 0;
	if (!buf)
		return (0);
	while (*buf)
	{
		if (*buf == c)
			return (ret + 1);
		buf++;
		ret++;
	}
	return (0);
}


/*USE MEM/STRCHR*/

char	*ft_strdup(char const *s)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	tmp = ft_calloc(ft_strlen(s) + 1, sizeof(*tmp));
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	return (tmp);
}

void	*ft_realloc(void *ptr, size_t size_new)
{
	void	*ptr_new;
	size_t	size_old;

	if (!ptr)
		return (ft_calloc(size_new, 1));
	size_old = ft_strlen((char const *)ptr);
	ptr_new = (char *)ft_calloc(sizeof(char), size_new);
	if (!ptr_new)
		return (NULL);
	ft_memcpy(ptr_new, ptr, size_old);
	free(ptr);
	return (ptr_new);
}

char	*input_line_extract(char *buf, char **left)
{
	ssize_t	input_line_len;
	char	*input_line;

	input_line_len = input_content_find(buf, '\n');
	input_line = ft_substr(buf, 0, input_line_len);
	if (!input_line)
	{
		free(buf);
		return (NULL);
	}
	*left = ft_strdup(buf + input_line_len);
	if (!*left)
	{
		free(input_line);
		free(buf);
		return (NULL);
	}
	free(buf);
	return (input_line);
}

char	*get_next_line(int fd)
{
	char *buf;
	char *left;
	size_t	buf_size;

	buf_size = 0;
	buf = NULL;
	while (!input_content_find(buf, '\n'))
	{
		buf_size += BUFFER_SIZE;
		buf = ft_realloc(buf, buf_size);
		if (read(fd, buf + ft_strlen(buf) < BUFFER_SIZE)
			return (input_line_extract(buf, &left));
	}
	return (input_line_extract(buf, &left));
}

int	main(void)
{
	int		input;
	int		output;
	char	*path_input = "./input";
	char	*path_output = "./output";
	char	*input_line_read;

	input = open(path_input, O_RDONLY);
	output = open(path_output, O_WRONLY);
	while (1)
	{
		input_line_read = get_next_line(input);
		write(output, input_line_read, ft_strlen(input_line_read));
		free (input_line_read);
		if (input_line_read == NULL)
			break ;
		input_line_read = NULL;
	}
	close(input);
	close(output);
	return (0);
}