NAME := pipex

CC := cc

CFLAGS := -Wall -Werror -Wextra -g

SRC := pipex.c gnl2/get_next_line.c gnl2/get_next_line_utils.c input_utils.c

LIBS := libft/libft.a printf/libftprintf.a

OBJ := $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) pipex.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
