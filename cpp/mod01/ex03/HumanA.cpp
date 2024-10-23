/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:14:18 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/23 11:34:01 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA( std::string name, Weapon &weapon ) : weapon(weapon), name(name)
{
	std::cout << "HumanA Created" << std::endl;
}

HumanA::~HumanA( void )
{
	std::cout << "HumanA Destroyed" << std::endl;
}

void	HumanA::setWeapon(Weapon &weapon)
{
	this->weapon = weapon;
	std::cout << this->name << " Changed Weapon to " << this->weapon.getType() << std::endl;
}

void	HumanA::attack( void ) const
{
	std::cout << this->name << " attacks with their " << this->weapon.getType() << std::endl;
}
