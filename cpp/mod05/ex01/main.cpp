/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:21 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/17 11:24:59 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main ( void )
{
    try
    {
        Form f("Some form", 0, 0);
    }
    catch( std::exception &e )
    {
        std::cout << "[EXCEPTION] caught: " << e.what() << std::endl;
    }

    try
    {
        Form f("Some form", 155, 155);
        Bureaucrat me("I", 49);
        me.signForm(f);
    }
    catch( std::exception &e )
    {
        std::cout << "[EXCEPTION] caught: " << e.what() << std::endl;
    }

    try
    {
        Form f("Some form", 50, 50);
        Bureaucrat me("I", 49);
        me.signForm(f);
    }
    catch( std::exception &e )
    {
        std::cout << "[EXCEPTION] caught: " << e.what() << std::endl;
    }

    try
    {
        Form f("Some form", 50, 50);
        Bureaucrat me("I", 51);
        me.signForm(f);
    }
    catch( std::exception &e )
    {
        std::cout << "[EXCEPTION] caught: " << e.what() << std::endl;
    }

    return 0;
}
