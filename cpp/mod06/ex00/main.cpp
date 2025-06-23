/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:23:38 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 15:36:29 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <exception>
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Invalid arguments!" << std::endl;
        return 1;
    }

    try {
        ScalarConverter::convert(argv[1]);
    } catch ( std::exception &e ) {
        std::cerr << e.what() << std::endl;
    }
}
