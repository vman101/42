# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: victor </var/spool/mail/victor>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 12:24:47 by victor            #+#    #+#              #
#    Updated: 2024/07/07 12:21:56 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC := cc

CFLAGS := -Wall -Wextra -lreadline -g3 -fsanitize=address,undefined,leak -static-libsan

LIBS := libft/libft.a

SRC := list.c input.c fts.c minishell.c list_memory.c command.c termios.c

OBJ := $(SRC:%.c=%.o)

BONOBJ := $(BONSRC:%.c=%.o)

all: $(NAME)

bonus: $(BONNAME)

$(NAME): $(OBJ) $(LIBS) minishell.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(BONNAME): $(BONOBJ) $(LIBS) minishell.h
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
