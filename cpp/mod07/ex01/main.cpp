/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:46:43 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/08 17:08:09 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "iter.hpp"
#include <iostream>

#define STRING_COUNT 3

void inc_one(std::string &c) {
    c[0]++;
}

int main() {
    std::string s[STRING_COUNT] = {"A", "B", "C"};
    iter(s, 3, inc_one);
    for (int i = 0; i < STRING_COUNT; i++) {
        std::cout << s[i] << std::endl;
    }
}
