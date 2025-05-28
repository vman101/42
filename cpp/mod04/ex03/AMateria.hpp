/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:46:09 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/28 12:04:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <string>
# include "DynamicArray.hpp"

class ICharacter;

class AMateria
{
protected:
    std::string     _type;
    static DynamicArray   _memory_collector;

public:
    AMateria();
    virtual ~AMateria();
    AMateria(const AMateria& other);
    AMateria& operator=(const AMateria& other);
    void *operator new(size_t);
    void operator delete(void *);
    AMateria(std::string const & type);

    std::string const & getType() const; //Returns the materia type
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};

#endif // !AMATERIA_HPP
