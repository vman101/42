/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:40:52 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/09 13:52:19 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main ( void )
{
    Zombie zomb("");
    Zombie *dyn = newZombie("");
    Zombie test;

    zomb.announce();
    dyn->announce();
    randomChump("Testing");

    delete dyn;
    return 0;
}
