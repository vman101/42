# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/16 13:02:01 by vvobis            #+#    #+#              #
#    Updated: 2024/06/16 13:41:08 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc

CFLAGS := -Wall -Wextra -Werror

LINK := -lXext -lX11 -lm -lmlx

NAME := fdf

SRC := fdf.c utils.c map.c map_create.c drawing.c rotation.c transformation.c setup.c glyph.c image.c loop.c map_correct.c

OBJ := $(SRC:.c=.o)

LIBDIR := libs

LIBS = $(LIBDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LINK)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(LIBS): $(LIBDIR)
	make bonus -C libft
	mv libft/libft.a libs/

$(LIBDIR):
	mkdir $@

clean:
	rm -f $(OBJ)
	rm -rf $(LIBDIR)
	make fclean -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all
