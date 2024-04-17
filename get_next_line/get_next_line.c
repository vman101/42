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

char	*handle_no_nl(char *left)
{
	if (ft_strlen(left))
		return (left);
	free(left);
	left = NULL;
	return (NULL);
}

char	*line_extract(char *left)
{
	char		*line;
	size_t		line_len;

	line_len = find_newline(left);
	if (line_len)
	{
		line = ft_substr(left, 0, line_len);
		if (!line)
			return (free(left), NULL);
		left = ft_strdup(left + line_len);
		if (!left)
			return (free(line), NULL);
		return (line);
	}
	return (handle_no_nl(left));
}

char	*get_next_line(int fd)
{
	char		*buf_fetch;
	ssize_t		bytes_read;
	static char	*left;

	buf_fetch = NULL;
	while (1)
	{
		free(buf_fetch);
		buf_fetch = NULL;
		buf_fetch = ft_calloc(sizeof(*buf_fetch), BUFFER_SIZE + 1);
		if (!buf_fetch)
			return (free(left), NULL);
		bytes_read = read(fd, buf_fetch, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf_fetch), free(left), NULL);
		if (bytes_read > 0)
			left = ft_strjoin(left, buf_fetch);
		if (find_newline(buf_fetch) || bytes_read == 0)
			return (free(buf_fetch), line_extract(left));
	}
	return (line_extract(left));
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
