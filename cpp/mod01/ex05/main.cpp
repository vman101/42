/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:21:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/23 15:42:52 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Harl.hpp"

int main (void)
{
	std::string	user_input;
	Harl		harl;

	while (std::getline(std::cin, user_input))
	{
		harl.complain(user_input);
	}
	return 0;
}
