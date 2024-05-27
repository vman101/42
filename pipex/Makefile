NAME := pipex

BONNAME := pipex_bonus

CC := cc

CFLAGS := -Wall -Werror -Wextra -g

LIBS := libft/libft.a

SRC := pipex.c list.c input.c commands.c pipe.c error.c 

BONSRC := pipex_bonus.c list.c input.c commands.c pipe.c error.c 

OBJ := $(SRC:%.c=%.o)

BONOBJ := $(BONSRC:%.c=%.o)

all: $(NAME)

bonus: $(BONNAME)

$(NAME): $(OBJ) $(LIBS) pipex.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(BONNAME): $(BONOBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $(BONNAME) $(BONOBJ) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

$(LIBS):
	make bonus -C libft

clean:
	make clean -C libft
	rm -f $(OBJ) $(BONOBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(BONNAME)

re: fclean all
