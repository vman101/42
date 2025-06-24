/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:26:14 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 16:45:35 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define MAX_ITER 100000

int main() {

    srandom(clock());
    Span sp = Span(MAX_ITER);
    do {
        sp.clear();
        for (int i = 0; i < MAX_ITER; i++) {
            sp.addNumber(random());
        }
    } while (0);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    return 0;
}
