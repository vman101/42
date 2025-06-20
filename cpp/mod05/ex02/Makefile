# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvobis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 12:51:08 by vvobis            #+#    #+#              #
#    Updated: 2025/06/20 16:11:59 by vvobis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := c++
CFLAGS := -Werror -Wextra -Wall -std=c++98 -MP -MD

NAME := form

SRC := PresidentialPardonForm.cpp ShrubberyForm.cpp RobotomyRequestForm.cpp Bureaucrat.cpp AForm.cpp main.cpp

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
