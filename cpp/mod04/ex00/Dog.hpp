/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:54:29 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 16:42:35 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"

class Dog: public Animal
{
public:
    Dog();
    ~Dog();

    Dog(const Dog&);
    Dog &operator=(const Dog& other);

    void makeSound() const;
};

#endif // !DOG_HPP
