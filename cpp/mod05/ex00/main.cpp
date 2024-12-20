/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:46:21 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/16 12:58:21 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"

int main ( void )
{
	try
	{
		Bureaucrat j("Jesus", 69);
		Bureaucrat e("Emil", 0);
	}
	catch( std::exception &e )
	{
		std::cout << "gotcha" << std::endl;
		std::cout << e.what() << std::endl;
	}
	return 0;
}
