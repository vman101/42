/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:14:25 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/08 16:45:44 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <iostream>
#include "PmergeMe.hpp"
#include "debug.hpp"
#include <cmath>

int F(int n) {
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

int main(int argc, char **argv) {
    if (argc <= 1 || argc > 10000) {
        std::cerr << "Invalid Argument Count" << std::endl;
    }

#ifdef DEBUG
    std::cout << "Expected number of comparisons: " << F(argc - 1) << std::endl;
#endif // DEBUG

    try {
        PmergeMe p(argv, argc);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
