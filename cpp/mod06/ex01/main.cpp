/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:40:24 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 18:09:27 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int main() {
    Data data;
    uintptr_t raw = Serialzer::serialize(&data);
    Data *redata = Serialzer::deserialize(raw);

    char *p;
    int *i = reinterpret_cast<int*>(p);

    std::cout << redata->getData() << std::endl;
}
