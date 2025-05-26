/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:41:41 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/26 14:40:01 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include <iostream>

AAnimal::AAnimal(): _type("Unidentified AAnimal")
{
    std::cout << "AAnimal constructor called" << std::endl;
}

AAnimal::~AAnimal()
{
    std::cout << "AAnimal destructor called" << std::endl;
}

AAnimal::AAnimal(const char *type) : _type(type)
{
    std::cout << "AAnimal string constructor called" << std::endl;
}

AAnimal::AAnimal(std::string type) : _type(type)
{
    std::cout << "AAnimal string constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other): _type(other._type)
{
    std::cout << "AAnimal copy constructor called" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal& other)
{
    if (this != &other)
    {
        _type = other._type;
    }
    return (*this);
}

const std::string& AAnimal::getType() const
{
    return _type;
}
