/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:46:43 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 14:18:07 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "iter.hpp"
#include <iostream>

void inc_one(const std::string &c) {
    c[0];
}

int main() {
    const std::string s[3] = {"A", "B", "C"};
    iter(s, 3, inc_one);
    for (int i = 0; i < 3; i++) {
        std::cout << s[i] << std::endl;
    }
}
