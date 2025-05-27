/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:18:25 by victor            #+#    #+#             */
/*   Updated: 2025/05/27 13:41:11 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include "AMateria.hpp"
#include "MateriaSource.hpp"
#include <sys/types.h>
#include "ICharacter.hpp"
#include "DynamicArray.hpp"

class Character : public ICharacter {
public:
    Character();
    Character(const std::string &name);
    Character(const Character &);
    Character &operator=(Character const &);
    ~Character();

    std::string const &getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
private:
    std::string _name;
    AMateria    *_materia_inventory[MATERIA_BUFFER_SIZE];
    int         _materia_index;

    DynamicArray      _memory_collector;

};

#endif // !CHARACTER_HPP
