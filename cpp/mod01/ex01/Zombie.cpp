/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:56:26 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/07 11:08:14 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie()
{
    std::cout << "[nameless zombie] has been created" << std::endl;
}

Zombie::Zombie(std::string name) :
	name(name)
{
    if (this->name.empty()) {
	    std::cout << "[nameless zombie] has been created" << std::endl;
    } else {
        std::cout << this->name << " has been created" << std::endl;
    }
}

Zombie::~Zombie()
{
    if (this->name.empty()) {
	    std::cout << "[nameless zombie] has been destroyed" << std::endl;
    } else {
        std::cout << this->name << " has been destroyed" << std::endl;
    }
}

void	Zombie::announce( void )
{
    if (this->name.empty()) {
	    std::cout << "[nameless zombie]: BraiiiiiiinnnzzzZ..." << std::endl;
    } else {
    	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
    }
}
