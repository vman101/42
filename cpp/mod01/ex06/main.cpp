/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:21:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/10/23 17:08:17 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main (int argc, char **argv)
{
	std::string	user_input;
	Harl		harl;

	if (argc != 2)
		return (1);
	user_input = argv[1];
	harl.complain(user_input);
	return 0;
}
