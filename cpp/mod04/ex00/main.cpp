/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:54:34 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 16:41:15 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    {
        const Animal* meta = new Animal();
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        std::cout << j->getType() << std::endl;
        std::cout << i->getType() << std::endl;
        i->makeSound(); //will output the cat sound!
        j->makeSound();
        meta->makeSound();
        delete meta;
        delete j;
        delete i;
    }
    {
        const WrongAnimal* wrong = new WrongAnimal();
        const WrongAnimal* catt = new WrongCat();
        wrong->makeSound();
        catt->makeSound();
        delete catt;
        delete wrong;
    }
}
