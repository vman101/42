/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:35:11 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 15:06:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"
#include <iostream>
#include "AMateria.hpp"
#include "Cure.hpp"
#include "Ice.hpp"

Vector::Vector() :
    _members(new AMateria*[VECTOR_DEFAULT_CAP]),
    _count(0),
    _cap(VECTOR_DEFAULT_CAP)
{
    std::cout << "Vector constructor called" << std::endl;
}

Vector::~Vector()
{
    std::cout << "Vector destructor called" << std::endl;
    for (int i = 0; i < this->_count; i++) {
            delete this->_members[i];
    }
    delete[] this->_members;
}

Vector::Vector(const Vector& other) :
    _count(other._count),
    _cap(other._cap)
{
    this->_members = new AMateria*[other._cap];
    for (int i = 0; i < other._cap; i++) {
        if (dynamic_cast<Ice *>(other._members[i])) {
            this->_members[i] = other._members[i]->clone();
        } else if (dynamic_cast<Cure *>(other._members[i])) {
            this->_members[i] = other._members[i]->clone();
        }
    }
    std::cout << "Vector copy constructor called" << std::endl;
}

Vector &Vector::operator=(const Vector& other)
{
    for (int i = 0; i < this->_count; i++) {
        delete this->_members[i];
    }

    delete[] this->_members;
    if (this != &other) {
        this->_members = new AMateria*[other._cap];
        for (int i = 0; i < other._cap; i++) {
            if (dynamic_cast<Ice *>(other._members[i])) {
                this->_members[i] = other._members[i]->clone();
            } else if (dynamic_cast<Cure *>(other._members[i])) {
                this->_members[i] = other._members[i]->clone();
            }
        }
        this->_cap = other._cap;
        this->_count = other._count;
        std::cout << "Vector assignment constructor called" << std::endl;
    }
    return (*this);
}

void Vector::push_unique(AMateria *new_mem) {
    for (int i = 0; i < this->_count; i++) {
        if (this->_members[i] == new_mem) {
            return ;
        }
    }
    this->push(new_mem);
}

void Vector::push(AMateria *new_mem) {
    if (this->_count == this->_cap) {
        this->_cap += VECTOR_DEFAULT_CAP;
        AMateria** new_mat = new AMateria*[this->_cap];
        for (int i = 0; i < this->_count; i++) {
            new_mat[i] = this->_members[i];
        }
        delete[] this->_members;
        this->_members = new_mat;
    }
    this->_members[this->_count] = new_mem;
    this->_count++;
}
