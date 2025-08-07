/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:35:35 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 20:47:46 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pair.hpp"
#include "AElement.hpp"
#include <iostream>

Pair::Pair()
{}

Pair::Pair(AElement *a, AElement *b):
    _pair(std::pair<AElement *, AElement *>(a, b))
{}

Pair::~Pair()
{}

Pair::Pair(const Pair& other)
    : _pair(other._pair)
{}

Pair &Pair::operator=(const Pair& other)
{
    if (this != &other)
        this->_pair = other._pair;
    return (*this);
}

AElement *Pair::getA( void ) {
    return this->_pair.second;
}

AElement *Pair::getB( void ) {
    return this->_pair.first;
}

int Pair::getValue() {
    return _pair.second->getValue();
}

void    Pair::print_value(void) {
    this->getA()->print();
}

void    Pair::print(void) {
    this->_pair.first->print();
    std::cout << " ";
    this->_pair.second->print();
}
