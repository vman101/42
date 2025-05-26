/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:10:22 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/26 18:13:10 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include "AMateria.hpp"

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
    return (*this);
}
