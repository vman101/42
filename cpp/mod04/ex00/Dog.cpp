/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:48:36 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 22:47:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <iostream>

Dog::Dog(): Animal()
{
	_type = "Dog";
	std::cout << "Dog constructor Called" << std::endl;
}

Dog::Dog(const Dog& other): Animal()
{
	_type = other._type;
}

Dog &Dog::operator=(const Dog& other)
{
	this->_type = other._type;
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog destuctor called" << std::endl;
}

void	Dog::makeSound( void ) const
{
	std::cout << "Meowww, aheum ahuem... Woof Woof" << std::endl;
}
