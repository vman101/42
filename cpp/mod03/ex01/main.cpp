/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:30:44 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/29 20:24:32 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	ClapTrap jesus("Jesus");

	jesus.attack("Satan");
	jesus.takeDamage(5);
	jesus.beRepaired(15);
	ScavTrap satan("Satan");
	satan.attack("Jesus");
	satan.guardGate();
}
