/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:55:30 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 15:55:32 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria
{
public:
    Ice();
    ~Ice();
    Ice(const Ice &);
    Ice &operator =(const Ice &);

    AMateria *clone() const;
    void use(ICharacter &target);
    bool isHeapAlloc() const;
private:
    bool    _is_heap_alloc;
};

#endif // ICE_HPP
