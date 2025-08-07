/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:53:35 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 20:49:40 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cctype>
#include <cstring>
#include <iostream>
#include "AElement.hpp"
#include "Number.hpp"
#include "Pair.hpp"
#include "debug.hpp"
#include <cstdlib>

/* EXCEPTIONS */

const char *PmergeMe::NotANumberException::what() const throw() {
    return "Invalid Input: Not A Number";
}

const char *PmergeMe::InvalidComparison::what() const throw() {
    return "Invalid comparison";
}

PmergeMe::PmergeMe() :
    _seq(std::vector<AElement *>())
{
    std::cout << "PmergeMe constructor called" << std::endl;
}

void    PmergeMe::solve(std::vector<AElement *> &v) {
    std::vector<AElement *> pairs;
    std::vector<AElement *> odds;

    uint32_t size = v.size();
    printSeq(v, YELLOW);

    if (size % 2 != 0) {
        AElement *end = v.back();
        odds.push_back(end);
    }

    for (uint32_t i = 0; i < v.size(); i += 2) {
        AElement *a = v[i];
        AElement *b = v[i + 1];
        switch (compare(a, b)) {
            case LESS:
                pairs.push_back(pair(a, b));
                break;
            case GREATER:
                pairs.push_back(pair(b, a));
                break;
            case EQUAL:
                break;
            default:
                break ;
        }
    }

    if (pairs.size() > 1) {
        solve(pairs);
    }

    std::cout << "Input vector      ";
    printSeq(pairs, YELLOW);

    {
        std::vector<AElement *> pend;
        std::vector<AElement *> main;
        for (unsigned int i = 0; i < pairs.size(); i++) {
            pend.push_back(pairs[i]->getB());
            main.push_back(pairs[i]->getA());
        }

        std::cout << "Main after split  ";
        printSeq(main, BLUE);

        std::cout << "pend after split  ";
        printSeq(pend, MAGENTA);
        /*printSeq(odds, GREEN);*/
        for (unsigned int i = 0; i < odds.size(); i++) {
            pend.push_back(odds[i]);
        }

        insert(main, pend);

        std::cout << "Main after insert ";
        printSeq(main, BLUE);
        v = main;
    }
}

void PmergeMe::insert(std::vector<AElement *> &main, std::vector<AElement*> &pend) {
    for (uint32_t i = 0; i < pend.size(); i++) {
        uint32_t span_low = 0;
        uint32_t span_high = main.size();
        while (span_low < span_high) {
            uint32_t center = span_low + (span_high - span_low) / 2;
            switch(compare(pend[i], main[center])) {
                case LESS:
                    /*std::cout << pend[i]->getValue() << " < " << main[center]->getValue() << std::endl;*/
                    span_high = center;
                    break;
                case GREATER:
                    /*std::cout << pend[i]->getValue() << " > " << main[center]->getValue() << std::endl;*/
                    span_low = center + 1;
                    break;
                default:
                    break;
            }
        }
        main.insert(main.begin() + span_low, pend[i]);
    }
}

void PmergeMe::printSeq(std::vector<AElement *> &v, const char *color) const {
    std::cout << color;
    for (unsigned int i = 0; i < v.size(); ++i) {
        std::cout <<  "[";
        v[i]->print();
        std::cout << "]";
    }
    std::cout << RESET << std::endl;
}

PmergeMe::PmergeMe(char **input, int count) :
    _seq(std::vector<AElement *>())
{
    for (int i = 1; i < count; i++) {
        for (uint32_t j = 0; j < std::strlen(input[i]); j++) {
            if (!std::isspace(input[i][j]))
                if (!std::isdigit(input[i][j]))
                    throw NotANumberException();
        }
        long long n = std::strtol(input[i], NULL, 10);
        AElement *e = new Number(n);
        _seq.push_back(e);
    }

    solve(_seq);
}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& other):
    _seq(other._seq)
{}

std::vector<AElement *> &PmergeMe::get_orig( void ) {
    return _seq;
}

PmergeMe &PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other) {
        this->_comp = other._comp;
        this->_seq = other._seq;
    }
    return (*this);
}

AElement    *PmergeMe::pair(AElement *a, AElement *b) {
    return new Pair(a, b);
}

comp_t  PmergeMe::compare(AElement *a, AElement *b) {
    _comp++;
    if (a->getValue() < b->getValue())
        return LESS;
    else if (a->getValue() > b->getValue())
        return GREATER;
    return EQUAL;
}
