/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:10:22 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 09:51:12 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include "AMateria.hpp"
#include "ICharacter.hpp"

#include <iostream>

Cure::Cure() : AMateria("cure")
{
    std::cout << "Cure constructor called" << std::endl;
}

Cure::~Cure()
{
    std::cout << "Cure destructor called" << std::endl;
}

Cure::Cure(const Cure& other) : AMateria("cure")
{
    if (this != &other) {
        this->_type = other._type;
    }
    std::cout << "Cure copy constructor called" << std::endl;
}

Cure &Cure::operator=(const Cure& other)
{
    if (this != &other) {
        if (other._type == "cure") {
            this->_type = "cure";
        } else {
            throw std::invalid_argument("Tried to create Materia of type cure from type " + other._type + "\n");
        }
    }
    return (*this);
}

AMateria *Cure::clone() const {
    return new Cure();
}

void Cure::use(ICharacter &target) {
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
