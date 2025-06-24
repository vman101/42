/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:43:24 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 12:15:07 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <exception>
#include <iostream>

Base::~Base() {}

Base *generate( void ) {
    srandom(clock());
    uint r = random() % 100;

    if (r < 33) {
        return new A();
    } else if (r < 66) {
        return new B();
    } else {
        return new C();
    }
}

void identify(Base *p) {
    std::cout << "This pointer is of type ";
    if (dynamic_cast<A*>(p)) {
        std::cout << "A";
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "B";
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "C";
    } else {
        std::cout << "unknown";
    }
    std::cout << std::endl;
}

void identify(Base &p) {
    std::cout << "This reference is of type ";
    try {
        A d = dynamic_cast<A&>(p);
        std::cout << "A";
        goto end;
    } catch (std::exception) {}

    try {
        B d = dynamic_cast<B&>(p);
        std::cout << "B";
        goto end;
    } catch (std::exception) {}

    try {
        C d = dynamic_cast<C&>(p);
        std::cout << "C";
        goto end;
    } catch (std::exception) {
        std::cout << "unknown";
    }

end:
    std::cout << std::endl;
}
