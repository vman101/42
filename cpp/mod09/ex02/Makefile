# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <victorvobis@web.de>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 14:12:12 by vvobis            #+#    #+#              #
#    Updated: 2025/08/08 16:42:23 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX := c++
CXXFLAGS := -Werror -Wextra -Wall -std=c++98 -MP -MD

NAME := PmergeMe

SRC := main.cpp PmergeMe.cpp Number.cpp Pair.cpp AElement.cpp

OBJ := $(SRC:%.cpp=%.o)
DEP := $(SRC:%.cpp=%.d)

all: $(NAME)

gdb: all
	gdb --args ./$(NAME) `shuf -i 1-99 -n 17 | tr "\n" " "`

test: debug
	@valgrind ./$(NAME) `shuf -i 1-50 -r -n 1000 | tr "\n" " "`

debug: all
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -g -D DEBUG" re

$(NAME): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(OBJ) $(DEP)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEP)
