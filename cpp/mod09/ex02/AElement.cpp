/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AElement.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:28:18 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 17:21:51 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AElement.hpp"


AElement::AElement()
{
}

AElement::~AElement()
{
}

AElement::AElement(const AElement& other)
{
    (void)other;
}

AElement &AElement::operator=(const AElement& other)
{
    (void) other;
    return (*this);
}
