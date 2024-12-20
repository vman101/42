/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:48:36 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 22:36:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>

Cat::Cat(): Animal()
{
	_type = "Cat";
	std::cout << "Cat constructor Called" << std::endl;
}

Cat::~Cat()
{
	std::cout << "Cat destuctor called" << std::endl;
}

Cat::Cat(const Cat& other): Animal()
{
	_type = other._type;
}

Cat &Cat::operator=(const Cat& other)
{
	this->_type = other._type;
	return (*this);
}

void	Cat::makeSound( void ) const
{
	std::cout << "Meowww" << std::endl;
}
