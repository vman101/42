/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:10:13 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 16:54:03 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"
#include <iostream>

WrongCat::WrongCat(): WrongAnimal()
{
    _type = "WrongCat";
    std::cout << "WrongCat constructor called" << std::endl;
}

WrongCat::~WrongCat()
{
    std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat::WrongCat(const std::string& type)
{
    this->_type = type;
    std::cout << "WrongCat string constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other): WrongAnimal(other._type)
{
    std::cout << "WrongCat copy constructor called" << std::endl;
}

void    WrongCat::makeSound( void ) const
{
    std::cout << "Hello, I am a WrongCat, nice to meet you." << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat& other)
{
    _type = other._type;
    return (*this);
}
