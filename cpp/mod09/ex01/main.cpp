/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:25:03 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/25 16:56:17 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>
#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>

int main(int argc, char **argv) {
    std::stringstream ss;
    std::stack<int> stack;

    if (argc < 2) {
        std::cerr << "[ERROR] Invalid argument count" << std::endl;
        return 1;
    }

    for (int i = 1; argv[i]; i++) {
        ss << argv[i];
        ss << " ";
    }

    try {
        RPN r(ss);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
