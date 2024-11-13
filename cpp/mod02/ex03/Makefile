# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 17:44:44 by vvobis            #+#    #+#              #
#    Updated: 2024/10/29 15:35:22 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := c++
CFLAGS := -Werror -Wextra -Wall -std=c++98 -MP -MD

NAME := fixed

SRC := Fixed.cpp Point.cpp main.cpp

OBJ := $(SRC:%.cpp=%.o)
DEP := $(SRC:%.cpp=%.d)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJ) $(DEP)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEP)
