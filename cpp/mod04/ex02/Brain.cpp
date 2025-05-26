/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:25:35 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/26 12:57:27 by vvobis           ###   ########.fr       */
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

Brain::Brain(const Brain& other) :
    _idea_index(other._idea_index)
{
    for (int i = 0; i < MAX_IDEAS; i++)
    {
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
        this->_idea_index = other._idea_index;
    }
    return (*this);
}

void Brain::haveIdea(const std::string& idea) {
    if (this->_idea_index == MAX_IDEAS)
        this->_idea_index = 0;
    this->_ideas[this->_idea_index++] = idea;
}

std::string Brain::expressIdea(int index) {
    std::string ret("");
    if (index >= 0 && index < this->_idea_index)
        ret = this->_ideas[index];
    return ret;
}
