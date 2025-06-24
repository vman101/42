/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:39:19 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 19:47:34 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>
# include <vector>

template <typename T>
class MutantStack: public std::stack< T, std::vector<T> > {
public:
    T *getData() {
        return this->c.data();
    }

    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    iterator begin( void );
    iterator end( void );
    const_iterator cbegin( void );
    const_iterator cend( void );
    const_reverse_iterator crbegin( void );
    const_reverse_iterator crend( void );
    reverse_iterator rbegin( void );
    reverse_iterator rend( void );
private:
};

#include "iterator.tpp"
#include "const_iterator.tpp"
#include "const_reverse_iterator.tpp"
#include "reverse_iterator.tpp"

#endif // MUTANTSTACK_HPP
