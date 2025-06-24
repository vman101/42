/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:26:32 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/24 16:50:31 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <exception>
# include <set>

class Span
{
public:
    Span();
    Span(unsigned int);
    ~Span();

    Span(const Span &);
    Span &operator=(const Span &);

    unsigned int    shortestSpan( void ) const;
    unsigned int    longestSpan( void ) const;
    void            addNumber( int n );
    void            clear(void);

    class NoRangePossible: public std::exception {
        const char * what() const throw();
    };

    class CapReached: public std::exception {
        const char * what() const throw();
    };

private:
    unsigned int    _cap;
    std::set<int>   _members;
};

#endif // SPAN_HPP
