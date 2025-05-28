/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicArray.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:35:11 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 12:29:24 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DynamicArray.hpp"
#include <cstring>
#include <iostream>
#include "Ice.hpp"

DynamicArray::DynamicArray() :
    _members(new void*[VECTOR_DEFAULT_CAP]),
    _count(0),
    _cap(VECTOR_DEFAULT_CAP)
{
    std::cout << "DynamicArray constructor called" << std::endl;
}

DynamicArray::~DynamicArray()
{
    std::cout << "DynamicArray destructor called" << std::endl;
    for (int i = 0; i < this->_count; i++) {
        this->manual_delete(this->_members[i]);
    }
    ::operator delete[](this->_members);
}

DynamicArray::DynamicArray(const DynamicArray& other) :
    _count(other._count),
    _cap(other._cap)
{
    this->_members = new void*[other._cap];
    for (int i = 0; i < other._cap; i++) {
        void *tmp = ::operator new(sizeof(other._members[i]));
        this->_members[i] = tmp;
    }
    std::cout << "DynamicArray copy constructor called" << std::endl;
}

DynamicArray &DynamicArray::operator=(const DynamicArray& other)
{
    for (int i = 0; i < this->_count; i++) {
        ::operator delete(this->_members[i]);
    }

    delete[] this->_members;
    if (this != &other) {
        this->_members = new void*[other._cap];
        for (int i = 0; i < other._cap; i++) {
            void *tmp = ::operator new(sizeof(other._members[i]));
            this->_members[i] = tmp;
        }
        this->_cap = other._cap;
        this->_count = other._count;
        std::cout << "DynamicArray assignment constructor called" << std::endl;
    }
    return (*this);
}

void DynamicArray::push_unique(void *new_mem) {
    for (int i = 0; i < this->_count; i++) {
        if (this->_members[i] == new_mem) {
            return ;
        }
    }
    this->push(new_mem);
}

void DynamicArray::push(void *new_mem) {
    if (this->_count == this->_cap) {
        this->_cap += VECTOR_DEFAULT_CAP;
        void** new_mat = new void*[this->_cap];
        for (int i = 0; i < this->_count; i++) {
            new_mat[i] = this->_members[i];
        }
        delete[] this->_members;
        this->_members = new_mat;
    }
    this->_members[this->_count] = new_mem;
    this->_count++;
}

void DynamicArray::manual_delete(void *member) {
    if (member) {
        AMateria *tmp = static_cast<AMateria*>(member);
        tmp->~AMateria();
        ::operator delete(member);
    }
}

void DynamicArray::remove(void *member) {
    for (int i = 0; i < this->_count; i++) {
        if (this->_members[i] == member) {
            std::memmove(&this->_members[i], &this->_members[i + 1], sizeof(this->_members[0]) * (this->_count - i - 1));
            this->_count--;
            break ;
        }
    }
}
