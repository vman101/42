/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:01:09 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/22 18:10:39 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main( void )
{
	Zombie *horde = zombieHorde(8, "Jesus");
	if (horde)
	{
		for (int i = 0; i < 8; i++)
			horde[i].announce();
		delete[] horde;
	}
}
