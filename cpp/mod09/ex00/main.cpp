/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:04:39 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/25 14:27:57 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <cstring>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "[ERROR] Invalid argument count" << std::endl;
        return 1;
    } else if (argv[1][0] == '0') {
        std::cerr << "[ERROR] Empty string detected" << std::endl;
        return 2;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "[ERROR] Failed to open file" << std::endl;
        if (errno != 0) {
            std::cerr << "System message: " << std::strerror(errno) << std::endl;
        }
        return 3;
    }

    try {
        BitcoinExchange b;
        b.extractRates(input);
    } catch (std::exception &e) {
        std::cerr << "Error encountered: " << e.what() << std::endl;
    }
}
