/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:16:43 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/07 11:11:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main()
{
	std::string string = "HI THIS IS BRAIN";
	std::string *stringPTR = &string;
	std::string &stringREF = string;

	std::cout << "string address: " << &string << std::endl;
	std::cout << "string ptr: " << stringPTR << std::endl;
	std::cout << "string ref: " << &stringREF << std::endl << std::endl;

	std::cout << "string value: " << string << std::endl;
	std::cout << "string ptr: " << *stringPTR << std::endl;
	std::cout << "string ref: " << stringREF << std::endl;
}
