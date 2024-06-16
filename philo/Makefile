CC := cc

CFLAGS := -Wall -Wextra -Werror -g
#3 -fsanitize=leak,address,undefined

NAME := philo

SRC := philo.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
