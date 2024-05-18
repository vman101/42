CC := cc

CFLAGS := -Wall -Wextra -Werror -g

LINK := -lXext -lX11

NAME := fdf

SRC := fdf.c

OBJ := $(SRC:.c=.o)

LIBS := libft/libft.a minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK)

%.o: %.c
	$(CC) -c $(SRC)

$(LIBS):
	make -C minilibx-linux
	make bonus -C libft
