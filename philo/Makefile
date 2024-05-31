CC := cc

CFLAGS := -Wall -Wextra -Werror -g
#3 -fsanitize=leak,address,undefined

NAME := philo

SRC := philo.c

OBJ := $(SRC:.c=.o)

LIBS := libs/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(LIBS):
	make bonus -C libft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
