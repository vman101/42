/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:54:29 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 19:16:39 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Brain.hpp"
# include "AAnimal.hpp"

class Dog: public AAnimal
{
public:
    Dog();
    ~Dog();

    Dog(const Dog&);
    Dog &operator=(const Dog& other);

    virtual void makeSound() const;
    Brain *getBrain() const;
private:
    Brain *brain;
};

#endif // !DOG_HPP
