/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:41:00 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 17:17:17 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_HPP
# define NUMBER_HPP

#include "AElement.hpp"
#include <exception>
class Number : public AElement
{
public:
    Number ();
    Number(const Number  &);
    Number (int);
    ~Number ();

    class NegativeValue: public std::exception {
        const char * what() const throw();
    };

    Number  &operator=(const Number  &);

    AElement    *getA();
    AElement    *getB();
    void        print( void );
    void        print_value( void );
    int         getValue( void );

private:
    int     _value;
};

#endif // NUMBER_HPP
