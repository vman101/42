/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:29:14 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 15:11:50 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap( void ) :
	ClapTrap()
{
	std::cout << "FragTrap Default constructor called" << std::endl;
	_hit_points = FRAGTRAP_DEF_HP;
	_energy_points = FRAGTRAP_DEF_EP;
	_attack_damage = FRAGTRAP_DEF_ATK;
}

FragTrap::FragTrap(const char *name) :
	ClapTrap(name)
{
	std::cout << "FragTrap String constructor called" << std::endl;
	_hit_points = FRAGTRAP_DEF_HP;
	_energy_points = FRAGTRAP_DEF_EP;
	_attack_damage = FRAGTRAP_DEF_ATK;
}

FragTrap::FragTrap(const FragTrap& other) :
    ClapTrap(other._name)
{
    std::cout << "FragTrap Copy Constructor Called" << std::endl;
    this->_hit_points = other._hit_points;
    this->_energy_points = other._hit_points;
    this->_attack_damage = other._attack_damage;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
    if (this != &other)
    {
        this->_name = other._name;
        this->_hit_points = other._hit_points;
        this->_energy_points = other._energy_points;
        this->_attack_damage = other._attack_damage;
    }
    std::cout << "Copy Assignment FragTrap constructor called" << std::endl;
    return (*this);
}


FragTrap::~FragTrap( void )
{
	std::cout << "FragTrap Destructor called" << std::endl;
}

void	FragTrap::highFivesGuys( void )
{
    if (this->_hit_points > 0)
    {
        std::cout << "FragTrap: Hey Guys, lets high five, i love you!" << std::endl;
    }
}
