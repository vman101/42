/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:54:34 by vvobis            #+#    #+#             */
/*   Updated: 2025/06/04 11:44:56 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>
#include <ostream>
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#define ANIMAL_COUNT 2

int main()
{
    Animal *tmp_animals[ANIMAL_COUNT] = { 0 };
    Animal *animals[ANIMAL_COUNT] = { 0 };

    Animal test_default;
    test_default.makeSound();

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2)
    {
            Dog *d = new Dog();

            tmp_animals[i] = d;

            Cat *c = new Cat();

            tmp_animals[i + 1] = c;
    }

    for (unsigned int i = 0; i < ANIMAL_COUNT; i += 2)
    {
        Dog d(*dynamic_cast<Dog *>(tmp_animals[i]));
        animals[i] = new Dog(d);
        Dog test_dog;
        test_dog = d;

        Cat c(*dynamic_cast<Cat *>(tmp_animals[i + 1]));
        Cat test_cat;
        test_cat = c;
        animals[i + 1] = new Cat(c);
        delete tmp_animals[i];
        delete tmp_animals[i + 1];
        animals[i]->makeSound();
        animals[i + 1]->makeSound();
    }

    WrongAnimal w_cat = WrongCat();
    WrongAnimal w_ani = WrongAnimal();

    std::cout << "This wrongcat says ";
    w_cat.makeSound();
    std::cout << "This wronganimal says ";
    w_ani.makeSound();

    for (int i = 0; i < ANIMAL_COUNT; i++) {
        delete animals[i];
    }
}
