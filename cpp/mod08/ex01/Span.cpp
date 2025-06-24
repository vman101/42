/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:29:52 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 16:21:52 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <limits.h>
#include <cstdlib>

const char* Span::NoRangePossible::what() const throw() {
    return "Trying to access empty member set";
}

const char* Span::CapReached::what() const throw() {
    return "Trying to add to full set";
}

Span::Span(): _cap(0), _members(std::set<int>()) {}


Span::Span(unsigned int N): _cap(N), _members(std::set<int>()) {}

Span::~Span() {}

Span::Span(const Span& other): _cap(other._cap), _members(other._members) {
}

Span &Span::operator=(const Span& other)
{
    if (this != &other) {
        this->_members = other._members;
        this->_cap = other._cap;
    }
    return (*this);
}

void    Span::addNumber(int n) {
    if (this->_members.size() == this->_cap) {
        throw CapReached();
    }
    this->_members.insert(n);
}

unsigned int Span::longestSpan( void ) const {
    if (this->_members.empty()) {
        throw NoRangePossible();
    } else if (this->_members.size() == 1) {
        throw NoRangePossible();
    }
    return *this->_members.rbegin() - *this->_members.begin();
}

unsigned int Span::shortestSpan( void ) const {
    if (this->_members.empty()) {
        throw NoRangePossible();
    } else if (this->_members.size() == 1) {
        throw NoRangePossible();
    }
    std::set<int>::const_iterator f = this->_members.begin();
    std::set<int>::const_iterator n = this->_members.begin();
    n++;

    long int min = UINT_MAX;

    for (; n != this->_members.end(); f++, n++) {
        if (*n - *f < min)
            min = (*n) - (*f);
    }
    return min;
}

void    Span::clear() {
    this->_members.clear();
}
