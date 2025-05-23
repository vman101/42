/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:39:56 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 15:31:06 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>


ScavTrap::ScavTrap() :
    ClapTrap()
{
    std::cout << "ScavTrap Default Constructor Called" << std::endl;
    this->_hit_points = SCAVTRAP_DEF_HP;
    this->_energy_points = SCAVTRAP_DEF_EP;
    this->_attack_damage = SCAVTRAP_DEF_ATK;
}

ScavTrap::ScavTrap(const char *name) :
    ClapTrap(name)
{
    std::cout << "ScavTrap Name Constructor Called" << std::endl;
    this->_hit_points = SCAVTRAP_DEF_HP;
    this->_energy_points = SCAVTRAP_DEF_EP;
    this->_attack_damage = SCAVTRAP_DEF_ATK;
}

ScavTrap::ScavTrap(const ScavTrap& other) :
    ClapTrap(other._name)
{
    std::cout << "ScavTrap Copy Constructor Called" << std::endl;
    this->_hit_points = other._hit_points;
    this->_energy_points = other._hit_points;
    this->_attack_damage = other._attack_damage;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
    if (this != &other)
    {
        this->_name = other._name;
        this->_hit_points = other._hit_points;
        this->_energy_points = other._energy_points;
        this->_attack_damage = other._attack_damage;
    }
    std::cout << "Copy Assignment ScavTrap constructor called" << std::endl;
    return (*this);
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap Destructor Called" << std::endl;
}

void    ScavTrap::attack(const std::string &target)
{
    std::cout   << "ScavTrap " << this->_name << " attacks " << target
                << ", dealing " << this->_attack_damage << " points of damage!"
                << std::endl;
}

void    ScavTrap::guardGate( void )
{
    std::cout << "ScavTrap is now in Gate Keeper Mode" << std::endl;
}
