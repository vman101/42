# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <victorvobis@web.de>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 14:12:12 by vvobis            #+#    #+#              #
#    Updated: 2025/08/07 18:42:33 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := c++
CFLAGS := -Werror -Wextra -Wall -std=c++98 -MP -MD -g

NAME := PmergeMe

SRC := main.cpp PmergeMe.cpp Number.cpp Pair.cpp AElement.cpp

OBJ := $(SRC:%.cpp=%.o)
DEP := $(SRC:%.cpp=%.d)

all: $(NAME)

gdb: all
	gdb --args ./$(NAME) `shuf -i 1-99 -n 17 | tr "\n" " "`

test: all
	@valgrind ./$(NAME) `shuf -i 1-99 -n 16 | tr "\n" " "`

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
