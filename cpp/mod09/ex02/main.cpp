/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:14:25 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 15:26:54 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <iostream>
#include "PmergeMe.hpp"
#include "debug.hpp"

int main(int argc, char **argv) {
    if (argc <= 1) {
        std::cerr << "Invalid Argument Count" << std::endl;
    }
    try {
        PmergeMe p(argv, argc);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
