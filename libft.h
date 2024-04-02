#include <unistd.h>
#include <stddef.h>

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
int ft_toupper();
int ft_tolower();
int ft_strchr();
int ft_strrchr();
int ft_strncmp();
int ft_memchr();
int ft_memcmp();
int ft_strnstr();
int ft_atoi();
