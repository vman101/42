/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:18:25 by victor            #+#    #+#             */
/*   Updated: 2025/05/26 19:23:24 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ICharacter.hpp"
#ifndef CHARACTER_HPP
# define CHARACTER_HPP

class Character : public ICharacter{
public:
    Character();
    Character(Character &);
    Character(const Character &);
    Character &operator=(Character &);
    ~Character();

    std::string const &getName() const;

private:
};

#endif // !CHARACTER_HPP
