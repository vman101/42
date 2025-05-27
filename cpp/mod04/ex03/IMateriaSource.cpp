/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:26:02 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 15:28:57 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMateriaSource.hpp"
#include <iostream>

IMateriaSource::~IMateriaSource() {
    std::cout << "IMateria Destructor called" << std::endl;
}
