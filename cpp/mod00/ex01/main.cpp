/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:46:06 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/07 17:07:53 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"
#include <iostream>

int main( void )
{
    Phonebook    Book;
    std::string    input;

    while (1)
    {
        std::cout << "Give Instruction (ADD/SEARCH/EXIT):" << std::endl;
        if (!std::getline(std::cin, input))
            break ;
        if (input == "ADD")
        {
            Book.Add();
        }
        else if (input == "SEARCH")
        {
            Book.Search();
        }
        else if (input == "EXIT")
        {
            break ;
        }
        else if (!input.empty()){
            std::cout << "[ERROR] Invalid Command, try again..." << std::endl;
        }
    }
}
