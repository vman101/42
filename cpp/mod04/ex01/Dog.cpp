/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:48:36 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 23:59:23 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <iostream>

Dog::Dog(): Animal()
{
	_type = "Dog";
	brain = new Brain();
	std::cout << "Dog constructor Called" << std::endl;
}

Dog::Dog(const Dog& other): Animal()
{
	_type = other._type;
}

Dog &Dog::operator=(const Dog& other)
{
	if (this != &other)
	{
		this->_type = other._type;
		delete brain;
		brain = new Brain(*other.brain);
		std::cout << "Dog Assignment operator called" << std::endl;
	}
	else
	{
		std::cout << "Attempting to copy same memory" << std::endl;
	}
	return (*this);
}

Dog::~Dog()
{
	delete brain;
	std::cout << "Dog destuctor called" << std::endl;
}

void	Dog::makeSound( void ) const
{
	std::cout << "Meowww, aheum ahuem... Woof Woof" << std::endl;
}
