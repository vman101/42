/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:59:05 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/26 19:14:33 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

#include "AMateria.hpp"
class Cure : AMateria
{
public:
    Cure();
    ~Cure();

    Cure(const Cure &);
    Cure &operator=(const Cure &);

    AMateria *clone() const;
    void use(ICharacter &target);

private:
};

#endif // !CURE_HPP
