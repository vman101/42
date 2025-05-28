# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 09:46:37 by vvobis            #+#    #+#              #
#    Updated: 2025/05/28 12:33:42 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := c++
CFLAGS := -Werror -Wextra -Wall -std=c++98 -MP -MD

NAME := amateria

SRC := AMateria.cpp Ice.cpp Cure.cpp main.cpp MateriaSource.cpp Character.cpp DynamicArray.cpp IMateriaSource.cpp

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
