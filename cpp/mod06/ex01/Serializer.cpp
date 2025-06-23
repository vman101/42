/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:13 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/23 18:08:16 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serialzer::Serialzer() {}

Serialzer::~Serialzer() {}

Serialzer::Serialzer(const Serialzer& other) { (void)other; }

Serialzer &Serialzer::operator=(const Serialzer& other)
{
    (void)other;
    return (*this);
}

uintptr_t   Serialzer::serialize(Data *ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data        *Serialzer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data *>(raw);
}
