/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:00:16 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/23 11:36:34 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB( std::string name ) : name(name)
{
	std::cout << "HumanB Created" << std::endl;
}

HumanB::~HumanB( void )
{
	std::cout << "HumanB Destroyed" << std::endl;
}

void	HumanB::setWeapon( Weapon &weapon )
{
	std::cout << this->name << " Changed Weapon to " << weapon.getType() << std::endl;
	this->weapon = &weapon;
}

void	HumanB::attack( void ) const
{
	if (this->weapon)
	{
		std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
	}
	else
	{
		std::cout << this->name << " is not holding a Weapon!" << std::endl;
	}
}
