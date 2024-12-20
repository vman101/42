/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:04:27 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 23:21:07 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"
#include <iostream>

WrongAnimal::WrongAnimal()
{
	std::cout << "WrongAnimal constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const std::string& type) : _type(type)
{
	std::cout << "WrongAnimal string constructor called" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal destructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other): _type(other._type)
{
	std::cout << "WrongAnimal copy constructor called" << std::endl;
}

void	WrongAnimal::makeSound( void ) const
{
	std::cout << "Weird, non animal sound..." << std::endl;
}

const std::string& WrongAnimal::getType() const
{
	return this->_type;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal& other)
{
	this->_type = other._type;
	return (*this);
}
