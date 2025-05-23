/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:32:06 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 14:37:25 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <climits>
#include <iostream>

void debug_print_line (const char *file, int line) {
    std::cout << "[" << file << ":" << line << "]\t";
}

ClapTrap::ClapTrap() :
    _name("default"),
    _hit_points(10),
    _energy_points(10),
    _attack_damage(0)
{
    std::cout << "Default ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) :
    _name(name),
    _hit_points(10),
    _energy_points(10),
    _attack_damage(0)
{
    std::cout << "String ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) :
    _name(other._name),
    _hit_points(other._hit_points),
    _energy_points(other._energy_points),
    _attack_damage(other._attack_damage)
{
    std::cout << "Copy ClapTrap constructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    if (this != &other)
    {
        this->_name = other._name;
        this->_hit_points = other._hit_points;
        this->_energy_points = other._energy_points;
        this->_attack_damage = other._attack_damage;
    }
    std::cout << "Copy Assignment ClapTrap constructor called" << std::endl;
    return (*this);
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap Destructor called" << std::endl;
}

void    ClapTrap::attack(const std::string &target)
{
    if (this->_hit_points <= 0)
        std::cout << "ClapTrap cant attack, it has no _hit_points left!" << std::endl;
    else if (this->_energy_points <= 0)
        std::cout << "ClapTrap cant attack, it has no _energy_points left!" << std::endl;
    else
    {
        std::cout    << "ClapTrap " << this->_name << " attacks " << target
            << ", dealing " << this->_attack_damage << " points of damage"
            << std::endl;
        this->_energy_points--;
    }
}

void    ClapTrap::takeDamage(unsigned int amount)
{
    if (this->_hit_points == 0)
    {
        std::cout    << "ClapTrap " << this->_name << " is already dead!" << std::endl;
        return ;
    }
    else
    {
        std::cout    << "ClapTrap " << this->_name << " receives " << amount
                    << " of damage, " ;
        if (amount > this->_hit_points)
        {
            this->_hit_points = 0;
            std::cout    << "ClapTrap " << this->_name << " has Died!" << std::endl;
            return ;
        }
        this->_hit_points -= amount;
        std::cout << "leaving " << this->_hit_points << " Hit Points"
            << std::endl;
    }
}

void    ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_hit_points == 0)
    {
        std::cout << "ClapTrap cant repair, it has no _hit_points left!" << std::endl;
    }
    else if (this->_energy_points == 0)
    {
        std::cout << "ClapTrap cant repair, it has no _energy_points left!" << std::endl;
    }
    else
    {
        if (amount > UINT_MAX - this->_hit_points)
        {
            std::cerr << "Overflow Detected When healing, how much health do you need?" << std::endl
                << "Setting Health to maximum" << std::endl;
            this->_hit_points = UINT_MAX;
        }
        else
        {
            this->_hit_points += amount;
            std::cout    << "ClapTrap " << this->_name << " healed "
                << amount << " up to " << this->_hit_points
                << std::endl;
        }
        this->_energy_points--;
    }
}
