NAME := push_swap
CC := cc
CFLAGS := -Wall -Wextra  -g

SRC := utils.c push_swap.c debug.c list.c ops.c input_setup.c
LIBS := libft/libft.a printf/libftprintf.a
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
