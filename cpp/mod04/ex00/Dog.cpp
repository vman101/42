/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:48:36 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 16:30:54 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <iostream>

Dog::Dog():
    Animal("Dog")
{
    std::cout << "Dog default constructor Called" << std::endl;
}

Dog::Dog(const Dog& other): Animal(other._type)
{
    std::cout << "Dog copy constructor Called" << std::endl;
}

Dog &Dog::operator=(const Dog& other)
{
    if (this != &other)
    {
        this->_type = other._type;
    }
    std::cout << "Dog assignment operator Called" << std::endl;
    return (*this);
}

Dog::~Dog()
{
    std::cout << "Dog destuctor called" << std::endl;
}

void    Dog::makeSound( void ) const
{
    std::cout << "Meowww, aheum ahuem... Woof Woof" << std::endl;
}
