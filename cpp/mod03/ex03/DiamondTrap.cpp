/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:59:06 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 09:44:34 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap( void ) :
    ClapTrap("default_clap_name"),
    ScavTrap(),
    FragTrap(),
    _name("default") {
    this->_hit_points = FragTrap::_hit_points;
    this->_energy_points = SCAVTRAP_DEF_EP;
    this->_attack_damage = FragTrap::_attack_damage;

    std::cout << "DiamondTrap " << this->_name << " constructed" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) :
    ClapTrap(name + "_clap_name"),
    ScavTrap(),
    FragTrap(),
    _name(name) {
    this->_hit_points = FragTrap::_hit_points;
    this->_energy_points = SCAVTRAP_DEF_EP;
    this->_attack_damage = FragTrap::_attack_damage;

    std::cout << "DiamondTrap default Constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) :
    ClapTrap(other.ClapTrap::_name),
    ScavTrap(),
    FragTrap(),
    _name(other._name)
{
    std::cout << "DiamondTrap Copy Constructor Called" << std::endl;
    this->_hit_points = other._hit_points;
    this->_energy_points = other._hit_points;
    this->_attack_damage = other._attack_damage;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other)
{
    if (this != &other)
    {
        this->_name = other._name;
        this->_hit_points = other._hit_points;
        this->_energy_points = other._energy_points;
        this->_attack_damage = other._attack_damage;
    }
    std::cout << "Copy Assignment DiamondTrap constructor called" << std::endl;
    return (*this);
}

void DiamondTrap::whoAmI(void) {
    std::cout << "I am " << this->_name << ", decendent of " << this->ClapTrap::_name << std::endl;
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap destructor called" << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target);
}
