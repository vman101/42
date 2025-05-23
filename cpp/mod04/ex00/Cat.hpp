/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:00:22 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 16:42:57 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal
{
public:
    Cat();
    ~Cat();

    Cat(const Cat&);
    Cat &operator=(const Cat&);

    void makeSound( void ) const;
};

#endif // !CAT_HPP
