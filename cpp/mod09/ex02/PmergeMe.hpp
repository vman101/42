/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:52:10 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 18:36:55 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGGEME_HPP
# define PMERGGEME_HPP

#include "AElement.hpp"
#include <exception>
#include <vector>

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

    void        solve(std::vector<AElement *> &v);
    void        insert(std::vector<AElement *> &main, std::vector<AElement*> &pend);

    void        solve_vec( std::vector<int> &);
    comp_t      compare(AElement *, AElement *);
    void        swap(int idx1, int idx2);
    AElement    *pair(AElement *, AElement *);

    void printSeq(std::vector<AElement *> &v, const char *color) const;

private:
    std::vector<AElement *> _seq;
    unsigned int            _comp;
};

#endif // PMERGGEME_HPP
