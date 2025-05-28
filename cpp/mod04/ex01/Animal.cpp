/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:41:41 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 19:12:17 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Brain.hpp"
#include <iostream>

Animal::Animal(): _type("Unidentified Animal")
{
    std::cout << "Animal constructor called" << std::endl;
}

Animal::~Animal()
{
    std::cout << "Animal destructor called" << std::endl;
}

Animal::Animal(const char *type) : _type(type)
{
    std::cout << "Animal string constructor called" << std::endl;
}

Animal::Animal(std::string type) : _type(type)
{
    std::cout << "Animal string constructor called" << std::endl;
}

Animal::Animal(const Animal& other): _type(other._type)
{
    std::cout << "Animal copy constructor called" << std::endl;
}

Animal &Animal::operator=(const Animal& other)
{
    if (this != &other)
    {
        _type = other._type;
    }
    return (*this);
}

void    Animal::makeSound( void ) const
{
    std::cout << "U silly, generic animals dont make sounds" << std::endl;
}

const std::string& Animal::getType() const
{
    return _type;
}
