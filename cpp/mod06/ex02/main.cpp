/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:15:13 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 12:05:03 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>

#define GEN_MAX 20

int main() {
    for (int i = 0; i < GEN_MAX; i++) {
        std::cout << "---------- Iter #" << i << " -----------" << std::endl;
        Base *b = generate();
        identify(b);
        identify(*b);
    }
}
