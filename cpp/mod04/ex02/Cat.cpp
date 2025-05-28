/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:48:36 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 10:27:03 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

Cat::Cat(): AAnimal("Cat"),
    brain(new Brain())
{
    std::cout << "Cat constructor Called" << std::endl;
}

Cat::~Cat()
{
    delete brain;
    std::cout << "Cat destuctor called" << std::endl;
}

Cat::Cat(const Cat& other):
    AAnimal(other._type),
    brain(new Brain(*other.brain))
{
    std::cout << "Cat copy destuctor called" << std::endl;
}

Cat &Cat::operator=(const Cat& other)
{
    if (this != &other)
    {
        this->_type = other._type;
        delete brain;
        brain = new Brain(*other.brain);
        std::cout << "Cat assignment operator called" << std::endl;
    }
    return (*this);
}

void    Cat::makeSound( void ) const
{
    std::cout << "Meowww" << std::endl;
}

Brain *Cat::getBrain() const {
    return this->brain;
}
