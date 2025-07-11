/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:01:09 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/07 11:14:31 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include "iostream"

int main( void )
{
	Zombie *horde = zombieHorde(8, "TestZombie");
	if (horde)
	{
		for (int i = 0; i < 8; i++)
        {
            horde[i].announce();
            std::cout << i << "# announced itself" << std::endl;
        }
		delete[] horde;
	}
}
