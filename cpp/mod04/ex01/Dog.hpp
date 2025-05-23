/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:54:29 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 19:05:30 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Brain.hpp"
# include "Animal.hpp"

class Dog: public Animal
{
public:
    Dog();
    ~Dog();

    Dog(const Dog&);
    Dog &operator=(const Dog& other);

    void makeSound() const;
    Brain& getBrain();
private:
    Brain *brain;
};

#endif // !DOG_HPP
