/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:00:22 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/26 12:40:30 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
public:
    Cat();
    ~Cat();

    Cat(const Cat&);
    Cat &operator=(const Cat&);

    void makeSound( void ) const;
    Brain *getBrain() const;
private:
    Brain *brain;
};

#endif // !CAT_HPP
