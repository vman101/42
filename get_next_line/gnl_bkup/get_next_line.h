/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/04/12 19:06:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
#endif

char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, void const *src, size_t n);
void	*ft_calloc(size_t n, size_t s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(char const *s);
