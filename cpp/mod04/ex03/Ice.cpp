/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:00:33 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 11:13:03 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "AMateria.hpp"
#include <iostream>

#include "ICharacter.hpp"

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
    AMateria("ice")
{
    (void)other;
    std::cout << "Ice copy constructor called" << std::endl;
}

Ice &Ice::operator=(const Ice& other)
{
    (void)other;
    return (*this);
}

AMateria *Ice::clone() const {
    return new Ice();
}

void Ice::use(ICharacter &target) {
    std::cout << "* shoots an ice bold at " << target.getName() << " *" << std::endl;
}
