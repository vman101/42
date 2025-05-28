/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:56:40 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/27 19:15:18 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <string>

class AAnimal
{
public:
    AAnimal();
    virtual ~AAnimal();

    AAnimal(const AAnimal&);
    AAnimal(std::string type);
    AAnimal(const char *type);
    AAnimal &operator=(const AAnimal&);

    virtual void makeSound( void ) const = 0;
    virtual const std::string& getType( void ) const;


protected:
    std::string _type;
};

#endif
