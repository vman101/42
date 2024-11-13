/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:29:14 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/29 20:34:06 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap( void ) : 
	ClapTrap()
{
	std::cout << "FragTrap Default constructor called" << std::endl;
}

FragTrap::FragTrap(const char *name) :
	ClapTrap(name)
{
	_hit_points = 100;
	_energy_points = 100;
	_attack_damage = 30;
}

FragTrap::~FragTrap( void )
{
	std::cout << "FragTrap Destructor called" << std::endl;
}

void	FragTrap::highFivesGuys( void )
{
	std::cout << "FragTrap: Hey Guys, lets high five, i love you!" << std::endl;
}
