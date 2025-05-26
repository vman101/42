/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:00:33 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/26 19:13:37 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "AMateria.hpp"
#include <iostream>


Ice::Ice() :
    AMateria("ice")
{
    std::cout << "Ice constructor called" << std::endl;
}

Ice::~Ice()
{
    std::cout << "Ice destructor called" << std::endl;
}

Ice::Ice(const Ice& other) :
    AMateria(other._type)
{
    std::cout << "Ice copy constructor called" << std::endl;
}

Ice &Ice::operator=(const Ice& other)
{
    if (this != &other) {
        this->_type = other._type;
    }
    return (*this);
}

AMateria *Ice::clone() const {
    return new Ice();
}

void Ice::use(ICharacter &target) {
    std::cout << "* shoots an ice bold at " << target.getName() << " *" << std::endl;
}
