/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:04:23 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 12:37:16 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "ICharacter.hpp"

#include <iostream>

AMateria::AMateria() :
    _type("undefined")
{
    std::cout << "AMateria constructor called" << std::endl;
}

AMateria::AMateria(const std::string& type) :
    _type(type)
{
    std::cout << "AMateria constructor called" << std::endl;
}

AMateria::~AMateria()
{
    std::cout << "AMateria destructor called" << std::endl;
}

AMateria::AMateria(const AMateria& other)
{
    this->_type = other._type;
    std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria &AMateria::operator=(const AMateria& other)
{
    if (this != &other) {
        this->_type = other._type;
    }
    return (*this);
}

std::string const& AMateria::getType() const {
    return this->_type;
}

void AMateria::use(ICharacter& target) {
    std::cout << "* does something to " << target.getName() << std::endl;
}
