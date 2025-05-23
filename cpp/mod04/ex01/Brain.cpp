/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:25:35 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 19:06:41 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <iostream>

Brain::Brain() :
    _idea_index(0)
{
    std::cout << "Brain constructor called" << std::endl;
}

Brain::~Brain()
{
    std::cout << "Brain destructor called" << std::endl;
}

Brain::Brain(const Brain& other)
{
    for (int i = 0; i < MAX_IDEAS; i++)
    {
        if (i < other._idea_index)
            this->_ideas[i] = other._ideas[i];
    }
    std::cout << "Brain copy constructor called" << std::endl;
}

Brain &Brain::operator=(const Brain& other)
{
    if (this != &other)
    {
        for (unsigned int i = 0; i < MAX_IDEAS; i++)
            this->_ideas[i] = other._ideas[i];
    }
    return (*this);
}

void Brain::haveIdea(const std::string& idea) {
    if (this->_idea_index == MAX_IDEAS)
        this->_idea_index = 0;
    this->_ideas[this->_idea_index] = idea;
}

std::string Brain::expressIdea(int index) {
    std::string ret("");
    if (index < 0 || index > this->_idea_index)
        ret = this->_ideas[index];
    return ret;
}
