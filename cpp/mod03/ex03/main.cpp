/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:30:44 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 15:23:23 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <climits>

#include <iostream>

int main()
{
    std::cout << std::endl << "--- Test functionality ---" << std::endl << std::endl;
    {
        debug_print_line(__FILE__, __LINE__);
        DiamondTrap trapHouse("TrapTrap");

        debug_print_line(__FILE__, __LINE__);
        DiamondTrap trappin(trapHouse);

        debug_print_line(__FILE__, __LINE__);
        trapHouse.attack("Opps");

        debug_print_line(__FILE__, __LINE__);
        trapHouse.takeDamage(200);

        debug_print_line(__FILE__, __LINE__);
        trapHouse.beRepaired(15);

        debug_print_line(__FILE__, __LINE__);
        trapHouse.takeDamage(5);

        debug_print_line(__FILE__, __LINE__);
        trapHouse = trappin;

        debug_print_line(__FILE__, __LINE__);
        trapHouse.attack("trappin");

        debug_print_line(__FILE__, __LINE__);
        trapHouse.highFivesGuys();

        debug_print_line(__FILE__, __LINE__);
        trapHouse.guardGate();

        debug_print_line(__FILE__, __LINE__);
        trapHouse.whoAmI();

    }

    std::cout << std::endl << "--- Test energy points ---" << std::endl << std::endl;
    // energy points tests
    {
        debug_print_line(__FILE__, __LINE__);
        DiamondTrap test("test");

        for (int i = 0; i < 11; i++) {
            debug_print_line(__FILE__, __LINE__);
            test.attack("target");
        }

        debug_print_line(__FILE__, __LINE__);
        test.beRepaired(20);
    }

    std::cout << std::endl << "--- Test overflow ---" << std::endl << std::endl;
    // overflows
    {
        debug_print_line(__FILE__, __LINE__);
        DiamondTrap over("flowing");

        /*over.beRepaired(UINT_MAX - 10);*/
        debug_print_line(__FILE__, __LINE__);
        over.takeDamage(UINT_MAX);

        debug_print_line(__FILE__, __LINE__);
        over.takeDamage(1);
    }
}
