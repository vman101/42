/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:07:36 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/18 20:19:03 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 20

# endif

# define MAX_FD 1024

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t n, size_t s);
size_t	ft_strlen(char const *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*line_handle(char **buf_fetch, int fd);
size_t	find_newline(char *buf);

#endif
