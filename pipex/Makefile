# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 11:54:30 by vvobis            #+#    #+#              #
#    Updated: 2024/06/15 12:37:20 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONNAME = pipex_bonus

CC := cc

CFLAGS := -Wall -Werror -Wextra

LIBS := libft/libft.a

SRC := pipex.c list.c input.c commands.c pipe.c error.c fts.c

BONSRC := pipex_bonus.c list.c input.c commands.c pipe.c error.c fts.c

OBJ := $(SRC:%.c=%.o)

BONOBJ := $(BONSRC:%.c=%.o)

all: $(NAME)

bonus: $(BONNAME)

$(NAME): $(OBJ) $(LIBS) pipex.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(BONNAME): $(BONOBJ) $(LIBS) pipex.h
	$(CC) $(CFLAGS) -o $(BONNAME) $(BONOBJ) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c $^

$(LIBS):
	make bonus -C libft

clean:
	make clean -C libft
	rm -f $(OBJ) $(BONOBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(BONNAME)

re: fclean all
