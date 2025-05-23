/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:48:36 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 16:28:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>

Cat::Cat() :
    Animal("Cat")
{
    std::cout << "Cat default constructor Called" << std::endl;
}

Cat::~Cat()
{
    std::cout << "Cat destuctor called" << std::endl;
}

Cat::Cat(const Cat& other) :
    Animal(other._type)
{
    std::cout << "Cat default constructor Called" << std::endl;
}

Cat &Cat::operator=(const Cat& other)
{
    if (this != &other)
        this->_type = other._type;
    return (*this);
}

void    Cat::makeSound( void ) const
{
    std::cout << "Meowww" << std::endl;
}
