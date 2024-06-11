NAME := push_swap
CC := cc
CFLAGS := -Wall -Wextra -Werror -g

SRC := utils.c push_swap.c list.c list2.c list3.c ops.c ops2.c ops3.c input_setup.c sort.c
LIBS := libft/libft.a
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

$(OBJ): $(SRC)
	$(CC) -c $(CFLAGS) $(SRC) 

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all
