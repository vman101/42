/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:53:35 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/08 17:17:13 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cctype>
#include <cerrno>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include "AElement.hpp"
#include "Number.hpp"
#include "Pair.hpp"
#include "debug.hpp"
#include <cstdlib>
#include <stdexcept>
#include <climits>

/* EXCEPTIONS */

const char *PmergeMe::NotANumberException::what() const throw() {
    return "Invalid Input: Not A Number";
}

const char *PmergeMe::InvalidComparison::what() const throw() {
    return "Invalid comparison";
}

PmergeMe::PmergeMe() :
    _seq(std::vector<AElement *>()),
    _comp(0)
{}

PmergeMe::~PmergeMe() {
    for (uint32_t i = 0; i < _allocs.size(); i++)
        delete _allocs[i];
}

PmergeMe::PmergeMe(const PmergeMe& other):
    _seq(other._seq)
{}

std::vector<AElement *> &PmergeMe::get_orig( void ) {
    return _seq;
}

PmergeMe &PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        this->_comp = other._comp;
        this->_seq = other._seq;
    }
    return (*this);
}

AElement    *PmergeMe::pair(AElement *a, AElement *b) {
    Pair *p = new Pair(a, b);
    _allocs.push_back(p);
    return p;
}

int PmergeMe::jakobsthal_number_fj(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jakobsthal_number_fj(n - 1) + 2 * jakobsthal_number_fj(n - 2);
}

void PmergeMe::solve_vec(void) {
    _comp = 0;

    std::vector<AElement *> v = _seq;
    unsigned long start = clock();
    solve(v);
    unsigned long end = clock();

    std::cout << "std::vector time for " << _seq.size() << " elements: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << "ms" << std::endl;

#ifdef DEBUG
    std::cout << "std::vector amount of comparisons:   " << _comp << std::endl;
#endif // DEBUG
}

void PmergeMe::solve_deq(void) {
    _comp = 0;

    std::deque<AElement *> d;
    for (uint32_t i = 0; i < _seq.size(); i++) {
        d.push_back(_seq[i]);
    }
    unsigned long start = clock();
    solve(d);
    unsigned long end = clock();

    std::cout << "After:  ";
    printSeqNoBracket(d, WHITE);

    std::cout << "std::deque time for " << _seq.size() << " elements: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << "ms" << std::endl;
#ifdef DEBUG
    std::cout << "std::deque amount of comparisons:    " << _comp << std::endl;
#endif // DEBUG
}

PmergeMe::PmergeMe(char **input, int count) :
    _seq(std::vector<AElement *>()),
    _comp(0)
{
    for (int i = 1; i < count; i++) {
        for (uint32_t j = 0; j < std::strlen(input[i]); j++) {
            if (!std::isspace(input[i][j]))
                if (!std::isdigit(input[i][j]))
                    throw NotANumberException();
        }
        long long n = std::strtol(input[i], NULL, 10);
        if (errno == ERANGE || n > INT_MAX || n < INT_MIN)
            throw std::logic_error("[Error] Value out of Range ");
        AElement *e = new Number(n);
        _allocs.push_back(e);
        _seq.push_back(e);
    }

    std::cout << "Before: ";
    printSeqNoBracket(_seq, WHITE);

    solve_deq();
    solve_vec();
}
