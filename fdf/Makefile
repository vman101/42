CC := cc

CFLAGS := -Wall -Wextra -Werror -g3 -fsanitize=leak,address,undefined

LINK := -lXext -lX11 -lm -lmlx

NAME := fdf

SRC := fdf.c utils.c map.c map_create.c drawing.c rotation.c transformation.c setup.c glyph.c image.c loop.c

OBJ := $(SRC:.c=.o)

LIBS := libs/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(LIBS):
	make bonus -C libft
	mv libft/libft.a libs/

clean:
	rm -f $(OBJ)
	rm -f $(LIBS)
	make fclean -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all
