/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:56:40 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/11 00:04:56 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <string>

class Animal
{
	public:
		Animal();
		virtual ~Animal();

		Animal(const Animal&);
		Animal(std::string &type);
		Animal &operator=(const Animal&);

		virtual void makeSound( void ) const = 0;
		const std::string& getType( void ) const;

	protected:
		std::string _type;
};

#endif
