/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:48:10 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 20:46:44 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Number.hpp"
#include "AElement.hpp"
#include <cstddef>
#include <iostream>

const char *Number::NegativeValue::what() const throw() {
    return "[ERROR] Negative Value detected";
}

Number::Number() : _value(0)
{}

Number::Number(int a) : _value(a) {
    if (a <= 0) {
        throw Number::NegativeValue();
    }
}

Number::~Number()
{}

Number::Number(const Number& other) : _value(other._value)
{}

Number &Number::operator=(const Number& other)
{
    if (this != &other)
        this->_value = other._value;
    return (*this);
}

AElement *Number::getA() {
    return this;
}

AElement *Number::getB() {
    return NULL;
}

int Number::getValue() {
    return _value;
}

void    Number::print_value( void ) {
    std::cout << " " << this->_value << "";
}

void    Number::print( void ) {
    std::cout << this->_value;
}
