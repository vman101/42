/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:56:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/22 18:04:32 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie()
{

}

Zombie::Zombie(std::string name) :
	name(name)
{
	std::cout << this->name << " has been created" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << this->name << " has been destroyed" << std::endl;
}

void	Zombie::announce( void )
{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
