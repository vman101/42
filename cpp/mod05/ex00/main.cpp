/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:21 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 14:27:48 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"

int main ( void )
{
    try
    {
        Bureaucrat j("Jesus", 69);
        Bureaucrat e("Emil", 1);
        std::cout << j << std::endl;
        std::cout << e << std::endl;
    }
    catch( std::exception &e )
    {
        std::cout << "[EXCEPTION] ";
        std::cout << e.what() << std::endl;
    }

    try
    {
        Bureaucrat j("Jesus", -1);
        Bureaucrat e("Emil", -15);
    }
    catch( std::exception &e )
    {
        std::cout << "[EXCEPTION] ";
        std::cout << e.what() << std::endl;
    }

    try
    {
        Bureaucrat j("Jesus", 150);
        Bureaucrat e("Emil", 149);
        e.decGrade();
        std::cout << e << std::endl;
        j.decGrade();
    }
    catch( std::exception &e )
    {
        std::cout << "[EXCEPTION] ";
        std::cout << e.what() << std::endl;
    }

    try
    {
        Bureaucrat j("Jesus", 1);
        Bureaucrat e("Emil", 2);
        e.incGrade();
        std::cout << e << std::endl;
        j.incGrade();
    }
    catch( std::exception &e )
    {
        std::cout << "[EXCEPTION] ";
        std::cout << e.what() << std::endl;
    }
    return 0;
}
