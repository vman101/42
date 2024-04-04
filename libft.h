#ifndef LIBFT_H
#define LIBFT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>

/* DEBUG */
void ft_putchar(char c);

int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isprint(int c);
int ft_isascii(int c);
int ft_strlen(char *str);
void *ft_memset(void *s, int c, size_t n);
void ft_bzero(void *s, size_t n);
void *ft_memcpy(void *dest, void *src, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);
size_t ft_strlcpy(char *dest, char *src, size_t size);
size_t ft_strlcat(char *dest, char *src, size_t size);
int ft_toupper(int c);
int ft_tolower(int c);
char *ft_strchr(char *s, int c);
char *ft_strrchr(char *s, int c);
int ft_strncmp(char *s1, char *s2, size_t n);
void *ft_memchr(void *s, int c, size_t n);
int ft_memcmp(void *s1, void *s2, size_t n);
char *ft_strnstr(char *s1, char *s2, size_t n);
int ft_atoi(char *s);

void *ft_calloc(size_t n, size_t s);

#endif
