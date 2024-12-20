/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:25:35 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 23:43:42 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <iostream>

Brain::Brain()
{
	std::cout << "Brain constructor called" << std::endl;
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

Brain::Brain(const Brain& other)
{
	for (unsigned int i = 0; i < sizeof(other.ideas) && i < sizeof(this->ideas); i++)
		this->ideas[i] = other.ideas[i];
	std::cout << "Brain copy constructor called" << std::endl;
}

Brain &Brain::operator=(const Brain& other)
{
	for (unsigned int i = 0; i < sizeof(other.ideas) && i < sizeof(this->ideas); i++)
		this->ideas[i] = other.ideas[i];
	return (*this);
}
