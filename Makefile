NAME := libft.a
CC := cc
CFLAGS:= -Wall -Wextra -Werror
SRC := ft_bzero.c ft_isalnum.c ft_isalpha.c	ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_isascii.c
OBJ := $(SRC:%.c=%.o)

all:
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) test.c

so: $(OBJ)
	$(CC) -shared -o libft.so $(OBJ)

$(OBJ): $(SRC)
	$(CC) -c $(CFLAGS) $(SRC)

clean:
	rm $(NAME) $(OBJ)
