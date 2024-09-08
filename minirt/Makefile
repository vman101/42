# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: victor </var/spool/mail/victor>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/08 16:30:33 by victor            #+#    #+#              #
#    Updated: 2024/09/08 23:12:45 by victor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc

CFLAGS := -Wall -Wextra -Werror -g3

LDFLAGS := -lmlx -lm -lXext -lX11

NAME := minirt

SRC := entry.c minirt_utils.c

LIBS := libft/libft.a memory/memory.a

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS) $(LDFLAGS)

$(OBJ): $(SRC) minirt.h
	$(CC) $(CFLAGS) -c $(SRC)

$(LIBS):
	make -C libft
	make -C memory

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
