CC := cc

CFLAGS := -Wall -Wextra -Werror -g3 
#-fsanitize=leak,address,undefined

NAME := philo

SRC := philo.c setup.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
