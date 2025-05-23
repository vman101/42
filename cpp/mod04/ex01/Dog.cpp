/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:48:36 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 19:17:51 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <iostream>

Dog::Dog():
    Animal("Dog"),
    brain(new Brain())
{
    std::cout << "Dog constructor Called" << std::endl;
}

Dog::Dog(const Dog& other):
    Animal(other._type)
{
    std::cout << "Dog copy constructor Called" << std::endl;
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
    return (*this);
}

Dog::~Dog()
{
    delete brain;
    std::cout << "Dog destructor called" << std::endl;
}

void    Dog::makeSound( void ) const
{
    std::cout << "Meowww, aheum ahuem... Woof Woof" << std::endl;
}

Brain& Dog::getBrain() {
    return *this->brain;
}
