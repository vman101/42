/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:48:36 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/11 00:00:19 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>

Cat::Cat(): Animal()
{
	_type = "Cat";
	brain = new Brain();
	std::cout << "Cat constructor Called" << std::endl;
}

Cat::~Cat()
{
	delete brain;
	std::cout << "Cat destuctor called" << std::endl;
}

Cat::Cat(const Cat& other): Animal()
{
	_type = other._type;
	std::cout << "Cat copy destuctor called" << std::endl;
}

Cat &Cat::operator=(const Cat& other)
{
	if (this != &other)
	{
		this->_type = other._type;
		delete brain;
		brain = new Brain(*other.brain);
		std::cout << "Cat Assignment operator called" << std::endl;
	}
	else
	{
		std::cout << "Attempting to copy same memory" << std::endl;
	}
	return (*this);
}

void	Cat::makeSound( void ) const
{
	std::cout << "Meowww" << std::endl;
}
