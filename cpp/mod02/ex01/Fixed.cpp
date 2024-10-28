/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:46:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/28 18:59:33 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &) : _value(0)
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed::Fixed(const int num) : _value(num << this->fraction_count)
{
	std::cout << "Integer constructor called" << std::endl;
}

Fixed::Fixed(const float value_new)
{
	std::cout << "Float constructor called" << std::endl;
	this->_value = roundf(value_new) * (1 << this->fraction_count);
}

Fixed &Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy operator called" << std::endl;
	if (this != &other)
	{
		_value = other._value;
	}
	return (*this);
}

int	Fixed::getRawBits()
{
	return this->_value;
}

void	Fixed::setRawBits( int const raw )
{
	this->_value = raw;
}
