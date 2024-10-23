/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:40:52 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/22 14:11:39 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main ( void )
{
	Zombie zomb("Jesus");
	Zombie *dyn = newZombie("Judas");

	zomb.announce();
	dyn->announce();
	randomChump("Satan");

	delete dyn;
	return 0;
}
