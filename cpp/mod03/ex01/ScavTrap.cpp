/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:39:56 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/29 20:17:08 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap() : ClapTrap()
{
	std::cout << "ScavTrap Default Constructor Called" << std::endl;
}

ScavTrap::ScavTrap(const char *name) : 
	ClapTrap(name)
{
	std::cout << "ScavTrap Name Constructor Called" << std::endl;
	_hit_points = 100;
	_energy_points = 50;
	_attack_damage = 20;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor Called" << std::endl;
}	

void	ScavTrap::attack(const std::string &target)
{
	std::cout	<< "ScavTrap " << _name << " attacks " << target
				<< ", dealing " << _attack_damage << " points of damage"
				<< std::endl;
}

void	ScavTrap::guardGate( void )
{
	std::cout << "ScavTrap is now in Gate Keeper Mode" << std::endl;
}
