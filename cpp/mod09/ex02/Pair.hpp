/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <victorvobis@web.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:25:17 by vvobis            #+#    #+#             */
/*   Updated: 2025/08/07 20:47:58 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include <AElement.hpp>
# include <utility>

class Pair : public AElement
{
public:
    Pair();
    Pair(AElement *, AElement *);
    ~Pair();

    Pair(const Pair &);
    Pair &operator=(const Pair &);

    AElement *  getA( void );
    AElement *  getB( void );
    void        print( void );
    void        print_value( void );
    int         getValue();

private:
    std::pair<AElement *, AElement *>   _pair;
};

#endif // PAIR_HPP
