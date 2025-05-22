/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:32:06 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/08 14:15:02 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

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
	std::cout << "Default ClapTrap constructor called" << std::endl;
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
		_name = other._name;
		_hit_points = other._hit_points;
		_energy_points = other._energy_points;
		_attack_damage = other._attack_damage;
	}
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor ClapTrap called" << std::endl;
}

void	ClapTrap::attack(const std::string &target)
{
	if (this->_hit_points <= 0)
		std::cout << "ClapTrap cant attack, it has no _hit_points left!" << std::endl;
	else if (_energy_points)
		std::cout << "ClapTrap cant attack, it has no _energy_points left!" << std::endl;
	else
	{
		std::cout	<< "ClapTrap " << _name << " attacks " << target
			<< ", dealing " << _attack_damage << " points of damage"
			<< std::endl;
		_energy_points--;
	}
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	_hit_points -= amount;
	if (_hit_points <= 0)
	{
		std::cout	<< "ClapTrap " << _name << " died!" << std::endl;
	}
	else 
	{
		std::cout	<< "ClapTrap " << _name << " receives " << amount
			<< " of damage, leaving " << _hit_points << " Hit Points"
			<< std::endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hit_points <= 0)
	{
		std::cout << "ClapTrap cant repair, it has no _hit_points left!" << std::endl;
	}
	else if (_energy_points)
	{
		std::cout << "ClapTrap cant repair, it has no _energy_points left!" << std::endl;
	}
	else
	{
		_hit_points += amount;
		std::cout	<< "ClapTrap " << _name << " healed "
			<< amount << " up to " << _hit_points 
			<< std::endl;
		_energy_points--;
	}
}
