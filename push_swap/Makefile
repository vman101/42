NAME := push_swap
CC := cc
CFLAGS := -Wall -Wextra -Werror -g

SRC := utils.c push_swap.c list.c list2.c ops.c ops2.c ops3.c ft_split.c ft_substr.c ft_calloc.c ft_atoi.c input_setup.c
LIBS := printf/libftprintf.a
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
