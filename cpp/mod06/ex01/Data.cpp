/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:44:27 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 18:07:44 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include <iostream>

Data::Data() :
    _data(42) {}

Data::~Data() {}

Data::Data(const Data& other) { (void)other; }

Data &Data::operator=(const Data& other)
{
    (void)other;
    return (*this);
}

int Data::getData() {
    return this->_data;
}
