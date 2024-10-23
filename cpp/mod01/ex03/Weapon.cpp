/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:28:05 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/23 11:26:05 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include <iostream>

Weapon::Weapon( std::string type) : type(type)
{
	std::cout << "Weapon Created" << std::endl;
}

Weapon::~Weapon()
{
	std::cout << "Weapon Destroyed" << std::endl;
}

void Weapon::setType(std::string type)
{
	this->type = type;
}

const std::string& Weapon::getType( void ) const
{
	return this->type;
}
