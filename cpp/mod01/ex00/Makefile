# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:46:34 by vvobis            #+#    #+#              #
#    Updated: 2024/10/22 14:05:51 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := c++

CFLAGS := -Werror -Wextra -Wall -std=c++98 -MP -MD

NAME := zombie

SRC := Zombie.cpp newZombie.cpp randomChump.cpp main.cpp

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
