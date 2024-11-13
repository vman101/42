/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:46:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/29 11:37:54 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>
#include <ostream>

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &to_copy) : _value(to_copy.getRawBits())
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
	this->_value = roundf(value_new * (1 << this->fraction_count));
}

float	Fixed::toFloat( void ) const
{
	return ((float)this->_value / (1 << this->fraction_count));
}

int		Fixed::toInt( void ) const
{
	return ((float)this->_value / (1 << this->fraction_count));
}

Fixed	&Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy operator called" << std::endl;
	if (this != &other)
	{
		_value = other._value;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &out, const Fixed &other)
{
	out << other.toFloat();
	return (out);
}

int			Fixed::getRawBits() const
{
	return this->_value;
}

void	Fixed::setRawBits( int const raw )
{
	this->_value = raw;
}
