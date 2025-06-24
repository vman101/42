/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:10:23 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 15:25:38 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <exception>
#include <list>
#include <iostream>

int main() {
    std::list<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    try {
        int i = easyfind(v, 2);
        std::cout << "Found member " << i << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        int i = easyfind(v, 6);
        std::cout << i << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
