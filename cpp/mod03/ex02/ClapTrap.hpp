/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:46:01 by vvobis            #+#    #+#             */
/*   Updated: 2025/05/23 14:12:15 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

#include <string>

class ClapTrap
{
public:
    ClapTrap();
    ClapTrap(std::string);
    ClapTrap(const ClapTrap &);
    ClapTrap &operator=(const ClapTrap &);
    ~ClapTrap();

    void    attack(const std::string &target);
    void    takeDamage(unsigned int amount);
    void    beRepaired(unsigned int amount);

protected:
    std::string     _name;
    unsigned int    _hit_points;
    unsigned int    _energy_points;
    unsigned int    _attack_damage;
};

void debug_print_line(const char *, int);


#endif // !CLAP_TRAP_HPP
