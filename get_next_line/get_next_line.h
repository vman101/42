/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:07:36 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/17 11:10:15 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 20

# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t n, size_t s);
size_t	ft_strlen(char const *str);
void	ft_memcpy(void *dest, void *src, size_t n);
char	*ft_strdup(char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*line_extract(char *left);

#endif
