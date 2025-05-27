/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:54:34 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 16:07:28 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>
#include <ostream>

#define ANIMAL_COUNT 10

int main()
{
    Animal *tmp_animals[ANIMAL_COUNT];
    Animal *animals[ANIMAL_COUNT];

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2)
    {
            Dog *d = new Dog();
            Brain *db = d->getBrain();

            db->haveIdea("I am A dog");
            tmp_animals[i] = d;

            Cat *c = new Cat();
            Brain *cb = c->getBrain();

            cb->haveIdea("I am A cat");
            tmp_animals[i + 1] = c;
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2)
    {
        Dog *d = new Dog(*dynamic_cast<Dog *>(tmp_animals[i]));
        animals[i] = d;
        Cat *c = new Cat(*dynamic_cast<Cat *>(tmp_animals[i + 1]));
        animals[i + 1] = c;
        delete tmp_animals[i];
        delete tmp_animals[i + 1];
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2) {
        std::cout << "This " << animals[i]->getType() << " thinks ";
        Brain *c = animals[i]->getBrain();
        std::cout << c->expressIdea(0) << std::endl;
        std::cout << "This " << animals[i + 1]->getType() << " thinks ";
        Brain *d = animals[i + 1]->getBrain();
        std::cout << d->expressIdea(0) << std::endl;
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2)
    {
        Brain *c = animals[i]->getBrain();
        Brain *d = animals[i + 1]->getBrain();
        Brain t(*d);
        *d = *c;
        *c = t;
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2) {
        std::cout << "This " << animals[i]->getType() << " thinks ";
        Brain* c = animals[i]->getBrain();
        std::cout << c->expressIdea(0) << std::endl;
        std::cout << "This " << animals[i + 1]->getType() << " thinks ";
        Brain *d = animals[i + 1]->getBrain();
        std::cout << d->expressIdea(0) << std::endl;
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2)
    {
        animals[i]->makeSound();
        delete animals[i];
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2) {
        std::cout << "This " << animals[i + 1]->getType() << " thinks ";
        Brain *d = animals[i + 1]->getBrain();
        std::cout << d->expressIdea(0) << std::endl;
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2)
    {
        animals[i + 1]->makeSound();
        delete animals[i + 1];
    }
}
