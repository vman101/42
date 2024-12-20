/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:54:34 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/11 00:07:24 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	Animal *animals[20];
	// vvv This will not compile because the class contains are pure virtual method
	// making it not instantiable
	// Animal *animal = new Animal();

	for (unsigned int i = 0; i < sizeof(animals) / 8; i++)
	{
		if (i % 2)
			animals[i] = new Cat();
		else
			animals[i] = new Dog();
	}

	for (unsigned int i = 0; i < sizeof(animals) / 8; i++)
	{
		animals[i]->makeSound();
		delete animals[i];
	}
}
