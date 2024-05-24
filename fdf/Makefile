CC := cc

CFLAGS := -Wall -Wextra -Werror -g

LINK := -lXext -lX11 -lm

NAME := fdf

SRC := fdf.c utils.c map.c map_create.c drawing.c debug.c rotation.c

OBJ := $(SRC:.c=.o)

LIBS := libs/libft.a libs/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK)

%.o: %.c
	$(CC) $(CFLAGS) -c $(SRC)

$(LIBS):
	make -C minilibx-linux
	make bonus -C libft
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
