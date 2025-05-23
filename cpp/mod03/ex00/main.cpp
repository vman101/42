/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:30:44 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 14:15:25 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <climits>

#include <iostream>

int main()
{
    std::cout << "--- Test functionality ---" << std::endl;
    // simple functionality
    {
        debug_print_line(__FILE__, __LINE__);
        ClapTrap trapHouse("TrapTrap");

        debug_print_line(__FILE__, __LINE__);
        ClapTrap trappin(trapHouse);

        debug_print_line(__FILE__, __LINE__);
        trapHouse.attack("Opps");

        debug_print_line(__FILE__, __LINE__);
        trapHouse.takeDamage(20);

        debug_print_line(__FILE__, __LINE__);
        trapHouse.beRepaired(15);

        debug_print_line(__FILE__, __LINE__);
        trapHouse.takeDamage(5);

        debug_print_line(__FILE__, __LINE__);
        trapHouse = trappin;

        debug_print_line(__FILE__, __LINE__);
        trapHouse.attack("trappin");
    }

    std::cout << "--- Test energy points ---" << std::endl;
    // energy points tests
    {
        debug_print_line(__FILE__, __LINE__);
        ClapTrap test("test");

        for (int i = 0; i < 11; i++) {
            debug_print_line(__FILE__, __LINE__);
            test.attack("target");
        }

        debug_print_line(__FILE__, __LINE__);
        test.beRepaired(20);
    }

    std::cout << "--- Test overflow ---" << std::endl;
    // overflows
    {
        debug_print_line(__FILE__, __LINE__);
        ClapTrap over("flowing");

        /*over.beRepaired(UINT_MAX - 10);*/
        debug_print_line(__FILE__, __LINE__);
        over.takeDamage(UINT_MAX);

        debug_print_line(__FILE__, __LINE__);
        over.takeDamage(1);
    }
}
