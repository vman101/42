# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:46:34 by vvobis            #+#    #+#              #
#    Updated: 2024/10/16 17:50:21 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := c++

CFLAGS := -Werror -Wextra -Wall

NAME := megaphone

SRC := megaphone.cpp
OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
