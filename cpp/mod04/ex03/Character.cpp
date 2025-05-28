/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:33:48 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 11:32:32 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "ICharacter.hpp"
#include "MateriaSource.hpp"
#include <iostream>
#include <sys/types.h>

Character::Character() :
    ICharacter(),
    _name("undefined"),
    _materia_index(0)
{
    for (uint i = 0; i < MATERIA_BUFFER_SIZE; i++) {
        this->_materia_inventory[i] = NULL;
    }
    std::cout << "Character constructor called" << std::endl;
}

Character::~Character()
{
    std::cout << "Character destructor called" << std::endl;
}

Character::Character(const Character& other) :
    _name(other._name),
    _materia_index(other._materia_index)
{
    for (uint i = 0; i < MATERIA_BUFFER_SIZE; i++) {
        if (other._materia_inventory[i])
            this->_materia_inventory[i] = other._materia_inventory[i]->clone();
        else {
            this->_materia_inventory[i] = NULL;
        }
    }
    std::cout << "Character copy constructor called" << std::endl;
}

Character &Character::operator=(const Character& other)
{
    if (this != &other) {
        for (uint i = 0; i < MATERIA_BUFFER_SIZE; i++) {
            if (other._materia_inventory[i])
                this->_materia_inventory[i] = other._materia_inventory[i]->clone();
            else {
                this->_materia_inventory[i] = NULL;
            }
        }
        this->_materia_index = other._materia_index;
    }
    return (*this);
}

Character::Character(const std::string &name) :
    ICharacter(),
    _name(name),
    _materia_index(0)
{
    for (uint i = 0; i < MATERIA_BUFFER_SIZE; i++) {
        this->_materia_inventory[i] = NULL;
    }
    std::cout << "Character name constructor called" << std::endl;
}

std::string const &Character::getName() const {
    return this->_name;
}

void Character::equip(AMateria* m) {
    if (!m) {
        std::cout << "[EQUIP_ERROR] Materia is NULL" << std::endl;
    } else if (this->_materia_index == MATERIA_BUFFER_SIZE) {
        std::cout << "[EQUIP_ERROR] Character " << this->_name << " has no free slots left" << std::endl;
    } else {
        for (int i = 0; i < MATERIA_BUFFER_SIZE; i++) {
            if (this->_materia_inventory[i] == m) {
        std::cout << "[EQUIP_ERROR] Character " << this->_name << " has already equipped this item" << std::endl;
                return ;
            }
        }
        for (int i = 0; i < MATERIA_BUFFER_SIZE; i++) {
            if (this->_materia_inventory[i] == NULL) {
                this->_materia_inventory[i] = m;
                this->_materia_index++;
                return ;
            }
        }
    }
}

void Character::unequip(int idx) {
    if (idx > MATERIA_BUFFER_SIZE || idx > this->_materia_index || idx < 0) {
        std::cout << "[UNEQUIP_ERROR] Slot " << idx << " on Character " << this->_name << " is not used" << std::endl;
    } else {
        this->_materia_index--;
        this->_materia_inventory[idx] = NULL;
    }
}

void Character::use(int idx, ICharacter& target) {
    if (idx > MATERIA_BUFFER_SIZE || this->_materia_inventory[idx] == NULL) {
        std::cout << "[USE_ERROR] Slot " << idx << " on Character " << this->_name << " is not used" << std::endl;
    } else {
        this->_materia_inventory[idx]->use(target);
    }
}
