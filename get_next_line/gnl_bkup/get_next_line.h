/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:07:36 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/15 19:10:00 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t n, size_t s);
size_t	ft_strlen(char const *str);
size_t	ft_strlcat(char *dest, char const *src, size_t size);
void	ft_memcpy(void *dest, void *src, size_t n);
char	*ft_strdup(char const *s);

# endif
