/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:52:10 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/08 16:41:25 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGGEME_HPP
# define PMERGGEME_HPP

#include "AElement.hpp"
#include <exception>
#include <vector>
#include <iostream>
#include <cstdlib>

typedef unsigned int uint32_t;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

typedef enum {
    LESS,
    GREATER,
    EQUAL
} comp_t;

int jakobsthal_number_fj(int n);

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(char **, int);
    ~PmergeMe();

    PmergeMe(const PmergeMe &);
    PmergeMe &operator=(const PmergeMe &);

    class NotANumberException: public std::exception {
        const char * what() const throw();
    };

    class InvalidComparison: public std::exception {
        const char * what() const throw();
    };

    std::vector<AElement *> &get_orig(void);

    void        solve_vec(void);
    void        solve_deq(void);

    void        swap(int idx1, int idx2);
    AElement    *pair(AElement *, AElement *);

    int         jakobsthal_number_fj(int n);

private:
    template <typename T>
    comp_t  compare(T *, T *);

    template <typename T>
    void    binary_insertion(T &main, T &pend);

    template <typename T>
    T       pair_up(T &v);

    template <typename T>
    T       split_and_insert(T &v, AElement *odd);

    template <typename T>
    void    solve(T &v);

    std::vector<AElement *> _seq;
    std::vector<AElement *> _allocs;
    unsigned int            _comp;
};

template <typename T>
T   PmergeMe::pair_up(T &v) {
    T pairs;
    for (uint32_t i = 0; i < v.size(); i += 2) {
        AElement *a = v[i];
        AElement *b = v[i + 1];
        switch (compare(a, b)) {
            case EQUAL:
            case LESS:
                pairs.push_back(pair(a, b));
                break;
            case GREATER:
                pairs.push_back(pair(b, a));
                break;
            default:
                break ;
        }
    }
    return pairs;
}

template <typename T>
comp_t  PmergeMe::compare(T *a, T *b) {
    _comp++;
    if (a->getValue() < b->getValue())
        return LESS;
    else if (a->getValue() > b->getValue())
        return GREATER;
    return EQUAL;
}

template <typename T>
void printSeqNoBracket(T &v, const char *color) {
    std::cout << color;
    for (unsigned int i = 0; i < v.size(); ++i) {
        v[i]->print();
        std::cout << " ";
    }
    std::cout << RESET << std::endl;
}

template <typename T>
void printSeq(T &v, const char *color) {
    std::cout << color;
    for (unsigned int i = 0; i < v.size(); ++i) {
        std::cout <<  "[";
        v[i]->print();
        std::cout << "]";
    }
    std::cout << RESET << std::endl;
}

template <typename T>
T   PmergeMe::split_and_insert(T &v, AElement *odd) {
    T pend;
    T main;
    for (unsigned int i = 0; i < v.size(); i++) {
        pend.push_back(v[i]->getB());
        main.push_back(v[i]->getA());
    }

    if (odd) {
        pend.push_back(odd);
    }

#ifdef DEBUG
    std::cout << "Main before insert ";
    printSeq(main, BLUE);
    std::cout << "Pend before insert ";
    printSeq(pend, MAGENTA);
    if (odd) {
        odd->print();
        std::cout << std::endl;
    }
#endif

    binary_insertion(main, pend);

#ifdef DEBUG
    std::cout << "Main after insert  ";
    printSeq(main, BLUE);
#endif

    return main;
}

template <typename T>
void PmergeMe::binary_insertion(T &main, T &pend) {
    if (pend.empty()) return;

    uint32_t previous_index = 1;
    uint32_t inserted_count = 1;

    main.insert(main.begin(), pend[0]);
    for (uint32_t k = 3; inserted_count < pend.size(); k++) {
        uint32_t jakobsthal_index = std::min(jakobsthal_number_fj(k), (int32_t)pend.size());

        for (uint32_t j = jakobsthal_index; j > previous_index && inserted_count < pend.size(); --j) {
            uint32_t i = j - 1;
            if (i >= pend.size())
                continue ;
            uint32_t upper = i + inserted_count;
            uint32_t lower = 0;

            while (lower < upper) {
                uint32_t    center = lower + (upper - lower) / 2;
                switch (compare(pend[i], main[center])) {
                    case LESS:
                        upper = center;
                        break ;
                    case GREATER:
                        lower = center + 1;
                        break ;
                    case EQUAL:
                        upper = center;
                    default:
                        break ;
                }
            }
            main.insert(main.begin() + lower, pend[i]);
            inserted_count++;
        }
        previous_index = std::min(jakobsthal_index, (uint32_t)pend.size());
    }
}

template <typename T>
void    PmergeMe::solve(T &v) {
    AElement * odd = NULL;

#ifdef DEBUG
    printSeq(v, YELLOW);
#endif

    if (v.size() % 2 != 0) {
        AElement *end = v.back();
        odd = end;
        v.pop_back();
    }

    T pairs = pair_up(v);

    if (pairs.size() > 1) {
        solve(pairs);
    }

#ifdef DEBUG
    std::cout << "Pairs vector       ";
    printSeq(pairs, YELLOW);
#endif

    v = split_and_insert(pairs, odd);
}


#endif // PMERGGEME_HPP
