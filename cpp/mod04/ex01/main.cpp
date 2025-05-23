/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:54:34 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 19:16:11 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>
#include <ostream>

#define ANIMAL_COUNT 20

int main()
{
    Animal *animals[ANIMAL_COUNT];

    for (unsigned int i = 0; i < ANIMAL_COUNT; i++)
    {
        if (i % 2)
        {
            Cat *c = new Cat();
            Brain& b = c->getBrain();

            b.haveIdea("I am A cat");
            animals[i] = c;
        }
        else
        {
            Dog *c = new Dog();
            Brain& b = c->getBrain();

            b.haveIdea("I am A dog");
            animals[i] = c;
        }
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2)
    {
        Brain& c = dynamic_cast<Cat*>(animals[i])->getBrain();
        Brain& d = dynamic_cast<Dog*>(animals[i + 1])->getBrain();
        Brain& t = d;
        d = c;
        c = t;
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i++) {
        std::cout << "This " << animals[i]->getType() << "thinks ";
        std::cout << "This " << animals[i + 1]->getType() << "thinks ";
        Brain& c = dynamic_cast<Cat*>(animals[i])->getBrain();
        Brain& d = dynamic_cast<Dog*>(animals[i + 1])->getBrain();
        std::cout << c.expressIdea(0) << std::endl;
        std::cout << d.expressIdea(0) << std::endl;
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i++)
    {
        animals[i]->makeSound();
        delete animals[i];
    }
}
